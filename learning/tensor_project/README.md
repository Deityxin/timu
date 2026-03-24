# AI Infra Project: MyTensor

这是你的第一个系统级 C++ 项目。目标是造一个简易的 Tensor 库。

## 如何运行
确保安装了 `cmake` 和 `g++` (MinGW 或 WSL)。

### 方式 1: 使用自动化脚本 (推荐)
在终端运行：
```powershell
.\build.ps1
```

### 方式 2: 手动编译
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles" # 如果是 Windows MinGW
# 或者
cmake .. # 如果是 Linux/WSL
make
./my_tensor
```

## 任务清单

### Level 1: 基础 (正在进行)
- [ ] 补全 `Matrix` 构造函数
- [ ] 实现 `at()` 方法的索引逻辑 `i * cols + j`
- [ ] 实现 `operator+`
- [ ] 通过 `main.cpp` 里的基本测试

### Level 2: 性能
- [ ] 实现朴素的 `operator*` (三重循环)
- [ ] 测量 1024x1024 矩阵乘法的时间
- [ ] 调整循环顺序 (i-j-k vs i-k-j)，观察性能变化 (Cache Locality)

### Level 3: 并发
- [ ] 使用 `#include <thread>` 或 OpenMP 将乘法并行化
