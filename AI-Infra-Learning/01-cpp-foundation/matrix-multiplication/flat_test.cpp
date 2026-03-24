#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

// ----------------------------------------------------------------------------------
// 听我说：别被代码吓到。
// 这里我们只做一个简单的改变：
// 把“很多个数组组成的二维数组”变成“仅仅一个长长的一维数组”。
// 就像把书从“很多个书架”搬到了“一条长长的传送带”上。
// ----------------------------------------------------------------------------------

int main() {
    int N = 1024; // 矩阵大小
    std::cout << "正在初始化 " << N << "x" << N << " 的矩阵 (一维数组模式)..." << std::endl;

    // 1. 只有这一行变了：大家都是一条线
    std::vector<double> A(N * N, 1.0);
    std::vector<double> B(N * N, 2.0);
    std::vector<double> C(N * N, 0.0);

    // 2. 也是 i-k-j 循环，但是取数据变简单了
    // 原来是: A[i][k] （要跳两次指针）
    // 现在是: A[i * N + k] （直接算地址，没有任何跳转）
    
    std::cout << "开始计算 (Flat Array)..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            
            // 这是一个微小的优化：把 A[i][k] 拿出来放在寄存器里
            double r = A[i * N + k]; 
            
            // 这是一个极其顺滑的内存访问：
            // B[k*N + j] 随着 j 的增加，内存地址是 +1 +1 +1 递增的
            // CPU 最喜欢这种！
            for (int j = 0; j < N; ++j) {
                C[i * N + j] += r * B[k * N + j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "计算完成！" << std::endl;
    std::cout << "耗时: " << elapsed.count() << " 秒" << std::endl;
    std::cout << "性能 (GFLOPS): " << (2.0 * N * N * N) / (elapsed.count() * 1e9) << std::endl;

    return 0;
}
