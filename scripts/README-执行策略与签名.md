# PowerShell 执行策略与脚本签名说明（Windows）

> 目的：确保 `scripts/toggle-exam.ps1` 等脚本可在你机器上顺利运行，并在需要时具备签名。

## 1) 放宽当前用户执行策略（推荐）
在 PowerShell（建议以“当前用户”范围）执行：
```pwsh
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned -Force
```
- 解释：允许本地脚本运行；从互联网下载的脚本需具备签名或解除阻止。

## 2) 解除文件阻止（如脚本通过网络获取）
```pwsh
Unblock-File -Path "d:\timu\scripts\toggle-exam.ps1"
```

## 3) （可选）自签名证书并为脚本签名
如果你的环境需要“必须签名”的策略，可自签名：
```pwsh
# 3.1 创建自签名代码签名证书（当前用户的“个人”存储）
$cert = New-SelfSignedCertificate -Type CodeSigningCert -Subject "CN=Dev Local Code Signing" -CertStoreLocation Cert:\CurrentUser\My

# 3.2 将证书复制到“受信任的根证书颁发机构”（提示同意）
$dest = 'Cert:\CurrentUser\Root'
Copy-Item -Path $cert.PSPath -Destination $dest

# 3.3 为脚本签名
Set-AuthenticodeSignature -FilePath "d:\timu\scripts\toggle-exam.ps1" -Certificate $cert
```
- 验证签名状态：
```pwsh
(Get-AuthenticodeSignature "d:\timu\scripts\toggle-exam.ps1").Status
```

## 4) 常见问题
- `无法加载文件...因为在此系统上禁止运行脚本`：执行第 1 步设置执行策略。
- `签名无效或证书不受信任`：执行第 3 步，将证书导入受信任的根；或将策略设为 RemoteSigned。
- 公司/学校设备：如有组策略限制，需联系管理员或仅使用“当前用户 + Unblock-File”。
