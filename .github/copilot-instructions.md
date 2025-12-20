# Copilot Instructions

- Repo purpose: competitive-programming practice in C++17; solutions live in `bits/shiyan` and `bits/test`, reusable snippets in `templates/`.
- Build/run: prefer VS Code task `C++: Run Current File` (builds with `g++ -std=gnu++17 -O2 -Wall -Wextra -I d:\timu` then runs the exe in the file directory). For manual runs in PowerShell: `g++ -std=gnu++17 -O2 -Wall -Wextra -I d:\timu your_file.cpp -o your_file.exe; .\your_file.exe`.
- Modes: use Tasks → `一键: 考试模式` or `一键: 正常模式` (or hotkeys Ctrl+Shift+Space / Ctrl+Alt+1). Under the hood `scripts/toggle-exam.ps1` writes `.vscode/MODE.*` markers and shows a notice; choose exam mode when you must avoid code completion.
- Templates: include `"common.hpp"` for fast IO (static initializer), aliases (`ll`, `pii`, `pll`), and helpers (`chmax/chmin`). Keep `using namespace std;` for consistency. Pull data-structure headers from `templates/` (Fenwick, segment tree, DSU, Dijkstra, KMP, LCA, sieve, fast_pow, trie, etc.) and include only what you use.
- Starter pattern: mirror `templates/template_main.cpp` — `#include <bits/stdc++.h>`, then `#include "common.hpp"`, add optional headers, and write `int main(){...}`. The template reads `n`, a vector, and outputs a sum; replace with the target algorithm.
- Snippets: in a new file type `cp` and press Enter for the main skeleton; type `inc-temp` to drop in common template includes.
- Path assumptions: headers are found via the repo root include path (`-I d:\timu`); keep source files inside the repo so includes like `"templates/segment_tree.hpp"` resolve without extra flags.
- OS/shell: environment is Windows + PowerShell; prefer PowerShell-friendly examples (no `&&`, use `;` or separate lines).
- Profiles: optional VS Code profiles live in `profiles/` (`exam.code-profile`, `normal.code-profile`) if you need to import them via `Profiles: Import Profile...`.
- Troubleshooting scripts: if `toggle-exam` is blocked, see `scripts/README-执行策略与签名.md` for execution policy and signing steps; markers and notices live under `.vscode/`.
- Keep outputs simple (stdout only) and avoid relying on non-ASCII unless a problem requires it; default to fast IO already enabled in `common.hpp`.
