# 自动构建脚本
$BuildDir = "build"

if (!(Test-Path -Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
    Write-Host "Created build directory."
}

Set-Location $BuildDir

# 尝试调用 CMake
Write-Host "Configuring with CMake..."
try {
    # 检查是否在 Windows 环境且非 WSL，尝试使用 MinGW 生成器
    if ($IsWindows) {
        cmake .. -G "MinGW Makefiles"
    } else {
        cmake ..
    }
} catch {
    Write-Error "CMake configuration failed. Please ensure CMake is installed."
    exit 1
}

# 编译
Write-Host "Building project..."
try {
    cmake --build .
} catch {
    Write-Error "Build failed."
    exit 1
}

# 运行
Write-Host "Running executable..."
if (Test-Path ".\my_tensor.exe") {
    .\my_tensor.exe
} elseif (Test-Path "./my_tensor") {
    ./my_tensor
} else {
    Write-Warning "Executable not found. Build might have failed."
}

Set-Location ..
