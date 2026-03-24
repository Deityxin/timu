#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>

// Level 1: 封装与内存管理
// 任务：补全 Matrix 类，替代 vector<vector<int>>
class Matrix {
private:
    int rows;
    int cols;
    // TODO: 思考为什么这里用一维数组比用 vector<vector<int>> 快？
    // 提示：Cache Locality (缓存局部性)
    std::vector<float> data; 

public:
    // 构造函数
    Matrix(int r, int c) : rows(r), cols(c) {
        // TODO: 初始化 data，大小为 rows * cols，初始值设为 0.0f
        // data.resize(...)
        std::cout << "Matrix constructed: " << rows << "x" << cols << std::endl;
    }

    // 析构函数 (如果使用 std::vector，C++ 会自动处理，但如果是 raw pointer 需要手动 delete)
    ~Matrix() {
        // Log 一下，感受 RAII (资源获取即初始化)
        // std::cout << "Matrix destroyed" << std::endl;
    }

    // 访问元素 (i, j)
    float& at(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[i * cols + j];
    }

    const float& at(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[i * cols + j];
    }

    // Level 1 任务: 实现加法
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions mismatch for addition");
        }
        Matrix result(rows, cols);
        // TODO: 实现矩阵加法
        // for (...) ...
        return result;
    }

    // Level 2 任务: 实现乘法 (重点优化对象)
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        }
        Matrix result(rows, other.cols);
        // TODO: 写出一个最朴素的三重循环矩阵乘法
        // 然后我们将尝试优化它的循环顺序
        return result;
    }

    void print() const {
        // 打印小矩阵用于调试
        if (rows > 10 || cols > 10) {
            std::cout << "[Matrix too large to print]" << std::endl;
            return;
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << at(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        std::cout << "=== AI Infra Project: Level 1 Start ===" << std::endl;

        // 1. 测试构造
        Matrix A(2, 2);
        // A.at(0, 0) = 1.0f; A.at(0, 1) = 2.0f;
        // A.at(1, 0) = 3.0f; A.at(1, 1) = 4.0f;

        Matrix B(2, 2);
        // B.at(0, 0) = 0.5f; ...

        // 2. 测试加法
        // Matrix C = A + B;
        // C.print();

        // 3. 测试乘法 (Level 2)
        // Matrix D = A * B;

        std::cout << "=== Success ===" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
