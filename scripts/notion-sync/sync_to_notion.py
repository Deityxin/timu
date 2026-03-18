#!/usr/bin/env python3
import argparse
import csv
import json
import os
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
from urllib import error, request

DEFAULT_NOTION_VERSION = "2022-06-28"


@dataclass
class Config:
    database_id: str
    csv_path: str
    dedupe_property: str
    notion_version: str
    columns: Dict[str, Dict[str, str]]


class NotionAPIError(RuntimeError):
    pass


def load_config(config_path: Path) -> Config:
    if not config_path.exists():
        raise FileNotFoundError(f"配置文件不存在: {config_path}")

    with config_path.open("r", encoding="utf-8") as f:
        data = json.load(f)

    required = ["database_id", "csv_path", "dedupe_property", "columns"]
    for key in required:
        if key not in data:
            raise ValueError(f"配置缺少字段: {key}")

    notion_version = data.get("notion_version", DEFAULT_NOTION_VERSION)
    return Config(
        database_id=str(data["database_id"]).replace("-", ""),
        csv_path=str(data["csv_path"]),
        dedupe_property=str(data["dedupe_property"]),
        notion_version=str(notion_version),
        columns=data["columns"],
    )


def notion_request(method: str, url: str, token: str, notion_version: str, body: Optional[Dict[str, Any]] = None) -> Dict[str, Any]:
    headers = {
        "Authorization": f"Bearer {token}",
        "Notion-Version": notion_version,
        "Content-Type": "application/json",
    }
    payload = None
    if body is not None:
        payload = json.dumps(body, ensure_ascii=False).encode("utf-8")

    req = request.Request(url=url, method=method, headers=headers, data=payload)
    try:
        with request.urlopen(req, timeout=30) as resp:
            text = resp.read().decode("utf-8")
            return json.loads(text) if text else {}
    except error.HTTPError as e:
        detail = e.read().decode("utf-8", errors="ignore")
        raise NotionAPIError(f"HTTP {e.code} {e.reason}: {detail}") from e
    except error.URLError as e:
        raise NotionAPIError(f"网络错误: {e.reason}") from e


def extract_title_text(prop_value: Dict[str, Any]) -> str:
    title_items = prop_value.get("title", [])
    return "".join(item.get("plain_text", "") for item in title_items).strip()


def get_existing_keys(config: Config, token: str) -> Dict[str, str]:
    url = f"https://api.notion.com/v1/databases/{config.database_id}/query"
    has_more = True
    cursor = None
    key_to_page_id: Dict[str, str] = {}

    while has_more:
        body: Dict[str, Any] = {"page_size": 100}
        if cursor:
            body["start_cursor"] = cursor

        result = notion_request("POST", url, token, config.notion_version, body)
        for page in result.get("results", []):
            props = page.get("properties", {})
            if config.dedupe_property not in props:
                continue
            value = props[config.dedupe_property]
            if value.get("type") != "title":
                continue
            key = extract_title_text(value)
            if key:
                key_to_page_id[key] = page.get("id", "")

        has_more = bool(result.get("has_more", False))
        cursor = result.get("next_cursor")

    return key_to_page_id


def parse_multi_values(raw: str) -> List[str]:
    parts = [p.strip() for p in re.split(r"[|,，;；]", raw) if p.strip()]
    seen = set()
    uniq_parts = []
    for p in parts:
        if p not in seen:
            seen.add(p)
            uniq_parts.append(p)
    return uniq_parts


def build_property(value: str, config_item: Dict[str, str]) -> Optional[Dict[str, Any]]:
    notion_type = config_item["type"]
    value = value.strip()

    if value == "":
        return None

    if notion_type == "title":
        return {"title": [{"text": {"content": value}}]}
    if notion_type == "rich_text":
        return {"rich_text": [{"text": {"content": value}}]}
    if notion_type == "select":
        return {"select": {"name": value}}
    if notion_type == "multi_select":
        return {"multi_select": [{"name": x} for x in parse_multi_values(value)]}
    if notion_type == "date":
        return {"date": {"start": value}}

    raise ValueError(f"不支持的字段类型: {notion_type}")


def row_to_notion_properties(row: Dict[str, str], config: Config) -> Dict[str, Any]:
    properties: Dict[str, Any] = {}

    for csv_col, rule in config.columns.items():
        notion_name = rule["notion_name"]
        notion_type = rule["type"]

        if csv_col not in row:
            continue

        item = build_property(row[csv_col], {"type": notion_type})
        if item is not None:
            properties[notion_name] = item

    return properties


def create_page(database_id: str, properties: Dict[str, Any], token: str, notion_version: str) -> str:
    url = "https://api.notion.com/v1/pages"
    body = {
        "parent": {"database_id": database_id},
        "properties": properties,
    }
    result = notion_request("POST", url, token, notion_version, body)
    return result.get("id", "")


def update_page(page_id: str, properties: Dict[str, Any], token: str, notion_version: str) -> str:
    url = f"https://api.notion.com/v1/pages/{page_id}"
    body = {"properties": properties}
    result = notion_request("PATCH", url, token, notion_version, body)
    return result.get("id", "")


def sync(config_path: Path, dry_run: bool, update_existing: bool) -> int:
    config = load_config(config_path)
    token = os.getenv("NOTION_TOKEN", "").strip()
    if not token:
        raise RuntimeError("未检测到环境变量 NOTION_TOKEN，请先设置后再运行。")

    csv_path = (config_path.parent / config.csv_path).resolve()
    if not csv_path.exists():
        raise FileNotFoundError(f"CSV 文件不存在: {csv_path}")

    with csv_path.open("r", encoding="utf-8-sig", newline="") as f:
        rows = list(csv.DictReader(f))

    if not rows:
        print("CSV 没有数据，不需要同步。")
        return 0

    existing_key_to_page = get_existing_keys(config, token)

    created = 0
    updated = 0
    skipped = 0

    for row in rows:
        dedupe_csv_col = None
        for col, rule in config.columns.items():
            if rule["notion_name"] == config.dedupe_property and rule["type"] == "title":
                dedupe_csv_col = col
                break

        if dedupe_csv_col is None:
            raise ValueError("配置错误: dedupe_property 必须映射到一个 title 类型字段")

        key = row.get(dedupe_csv_col, "").strip()
        if not key:
            skipped += 1
            continue

        properties = row_to_notion_properties(row, config)
        if config.dedupe_property not in properties:
            skipped += 1
            continue

        exists = key in existing_key_to_page

        if dry_run:
            action = "UPDATE" if (exists and update_existing) else ("SKIP" if exists else "CREATE")
            print(f"[DRY-RUN] {action}: {key}")
            continue

        if exists and update_existing:
            page_id = existing_key_to_page[key]
            update_page(page_id, properties, token, config.notion_version)
            updated += 1
            print(f"[UPDATED] {key}")
        elif exists:
            skipped += 1
            print(f"[SKIPPED] {key}")
        else:
            create_page(config.database_id, properties, token, config.notion_version)
            created += 1
            print(f"[CREATED] {key}")

    print("\n同步完成")
    print(f"- 新增: {created}")
    print(f"- 更新: {updated}")
    print(f"- 跳过: {skipped}")
    print(f"- 总计: {len(rows)}")

    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="将本地 CSV 刷题数据同步到 Notion 数据库")
    parser.add_argument("--config", default="config.json", help="配置文件路径，默认 config.json")
    parser.add_argument("--dry-run", action="store_true", help="演练模式：只打印动作，不写入 Notion")
    parser.add_argument("--update-existing", action="store_true", help="若记录已存在则更新，否则默认跳过")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    config_path = Path(args.config).resolve()
    try:
        return sync(config_path=config_path, dry_run=args.dry_run, update_existing=args.update_existing)
    except Exception as e:
        print(f"错误: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
