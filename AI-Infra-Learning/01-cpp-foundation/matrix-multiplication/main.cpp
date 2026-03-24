#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Using double for better precision in scientific computing
using Matrix = std::vector<std::vector<double>>;

// Function to initialize a random matrix
Matrix create_random_matrix(int rows, int cols) {
    Matrix matrix(rows, std::vector<double>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Naive implementation: 3 nested loops (Row-major)
// Expected complexity: O(N^3)
Matrix multiply_naive(const Matrix& A, const Matrix& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication.");
    }

    Matrix C(rowsA, std::vector<double>(colsB, 0.0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// 🚀 Optimization 1: Loop Reordering (i-k-j)
// By swapping the inner loops, we access B[k][j] row-wise (contiguous memory),
// which drastically improves CPU cache hit rate.
Matrix multiply_reordered(const Matrix& A, const Matrix& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    // Resize C directly
    Matrix C(rowsA, std::vector<double>(colsB, 0.0));

    for (int i = 0; i < rowsA; ++i) {
        for (int k = 0; k < colsA; ++k) {
             // Pre-fetch A[i][k]
            double r = A[i][k];
            for (int j = 0; j < colsB; ++j) {
                C[i][j] += r * B[k][j];
            }
        }
    }
    return C;
}

// 🚀 Optimization 2: Tiled Multiplication (Cache Blocking)
// Divide the matrix into small blocks that fit into CPU cache (L1/L2)
Matrix multiply_tiled(const Matrix& A, const Matrix& B, int blockSize = 32) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    Matrix C(rowsA, std::vector<double>(colsB, 0.0));

    // Iterate over blocks
    for (int i0 = 0; i0 < rowsA; i0 += blockSize) {
        for (int k0 = 0; k0 < colsA; k0 += blockSize) {
            for (int j0 = 0; j0 < colsB; j0 += blockSize) {
                
                // Process each block (mini matrix multiplication)
                // Limit boundaries to handle edges
                int i_max = std::min(i0 + blockSize, rowsA);
                int k_max = std::min(k0 + blockSize, colsA);
                int j_max = std::min(j0 + blockSize, colsB);

                for (int i = i0; i < i_max; ++i) {
                    for (int k = k0; k < k_max; ++k) {
                        double r = A[i][k];
                        for (int j = j0; j < j_max; ++j) {
                            C[i][j] += r * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}

int main() {
    // 1. Setup
    const int N = 1024; // Increase N to see Tiled benefits clearly
    std::cout << "Initializing matrices of size " << N << "x" << N << "..." << std::endl;

    auto A = create_random_matrix(N, N);
    auto B = create_random_matrix(N, N);

    // 2. Run Reordered & Time it (Baseline for this test)
    std::cout << "Running Reordered Implementation (i-k-j)..." << std::endl;
    auto start_reordered = std::chrono::high_resolution_clock::now();
    auto C_reordered = multiply_reordered(A, B);
    auto end_reordered = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_reordered = end_reordered - start_reordered;
    std::cout << "Reordered Time: " << elapsed_reordered.count() << "s | Performance: " 
              << (2.0 * N * N * N) / (elapsed_reordered.count() * 1e9) << " GFLOPS" << std::endl;

    // 3. Run Tiled & Time it
    std::cout << "\nRunning Tiled Implementation (Block Size = 32)..." << std::endl;
    auto start_tiled = std::chrono::high_resolution_clock::now();
    auto C_tiled = multiply_tiled(A, B, 32); // 32 is a common L1 cache block fit
    auto end_tiled = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_tiled = end_tiled - start_tiled;
    std::cout << "Tiled Time:     " << elapsed_tiled.count() << "s | Performance: " 
              << (2.0 * N * N * N) / (elapsed_tiled.count() * 1e9) << " GFLOPS" << std::endl;
    
    std::cout << "\nSpeedup (Tiled vs Reordered): " << elapsed_reordered.count() / elapsed_tiled.count() << "x" << std::endl;

    return 0;
}
