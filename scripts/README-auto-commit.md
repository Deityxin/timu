# Daily Auto Commit

This repo includes two scripts for automatic daily commits:

- `scripts/auto-commit.ps1`
  - Checks whether the repository has changes.
  - Runs `git add -A` and creates a commit only when changes exist.
  - Does nothing when the working tree is clean.
- `scripts/register-auto-commit-task.ps1`
  - Registers a Windows Scheduled Task that runs `auto-commit.ps1` once every day.

## Default behavior

- Repository path: `d:\timu`
- Task name: `timu-daily-auto-commit`
- Run time: `21:00`
- Default action: commit only, no push

## Re-register at a different time

```pwsh
pwsh -File d:\timu\scripts\register-auto-commit-task.ps1 -Time 22:30
```

## Enable automatic push too

```pwsh
pwsh -File d:\timu\scripts\register-auto-commit-task.ps1 -Push
```

## Safe verification without creating a commit

```pwsh
pwsh -File d:\timu\scripts\auto-commit.ps1 -DryRun
```

## Logs

The runtime log is written outside the repo so it will not create extra git changes:

`%LOCALAPPDATA%\timu\logs\auto-commit.log`
