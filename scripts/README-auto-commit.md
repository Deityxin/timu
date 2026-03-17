# Daily Auto Commit

This repo includes two scripts for automatic daily commits:

- `scripts/auto-commit.ps1`
  - Checks whether the repository has changes.
  - Runs `git add -A` and creates a commit only when changes exist.
  - Generates commit title/body automatically from staged changes
    (file type + stats + changed file list).
  - Does nothing when the working tree is clean.
- `scripts/register-auto-commit-task.ps1`
  - Registers a Windows Scheduled Task that runs `auto-commit.ps1` once every day.
- `scripts/auto-push-pending.ps1`
  - Checks whether the remote is reachable.
  - Pushes local pending commits when the network is available again.
- `scripts/register-auto-push-task.ps1`
  - Registers a Windows Scheduled Task.
  - The task checks for pending pushes every few minutes.

## Default behavior

- Repository path: `d:\timu`
- Task name: `timu-daily-auto-commit`
- Run time: `21:00`
- Default action: commit only, no push
- Commit title: automatically generated, e.g. `chore(auto): 更新题解与脚本 (4 files, +68/-12)`
- Commit body: automatically includes scope/stats and changed files list

## Intelligent message rules

- Detects staged changes by `git diff --cached --name-status` / `--numstat`
- Classifies files (e.g. 题解/模板/脚本/文档/配置)
- Chooses title action (`新增` / `清理` / `重命名` / `更新`) based on change type
- Builds title as: `chore(auto): {动作}{分类} ({文件数} files, +{新增}/-{删除})`
- Adds a body section with scope + stats + up to first 20 changed files

## Re-register at a different time

```pwsh
pwsh -File d:\timu\scripts\register-auto-commit-task.ps1 -Time 22:30
```

## Enable automatic push too

```pwsh
pwsh -File d:\timu\scripts\register-auto-commit-task.ps1 -Push
```

## Enable automatic retry push after the network comes back

```pwsh
pwsh -File d:\timu\scripts\register-auto-push-task.ps1 -IntervalMinutes 15
```

## Safe verification without creating a commit

```pwsh
pwsh -File d:\timu\scripts\auto-commit.ps1 -DryRun
```

## Logs

The runtime log is written outside the repo so it will not create extra git changes:

`%LOCALAPPDATA%\timu\logs\auto-commit.log`

`%LOCALAPPDATA%\timu\logs\auto-push.log`
