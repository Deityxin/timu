#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int prepare(int a) {
    int n = static_cast<int>((-1 + sqrt(1.0 + 8.0 * a)) / 2.0);
    if (n * (n + 1) / 2 < a) n += 1; // 若三角和不足则进一
    return n;
}
int main() {
    int count;
    cin >> count;
    int c = prepare(count);               // 对角线编号
    int prev_sum = c * (c - 1) / 2;       // 前一条对角线的项数总和
    int idx_in_diag = count - prev_sum;   // 本对角线内的序号(1-based)
    int num, den;
    if (c % 2 == 0) {                     // 偶数对角线：分子递增、分母递减
        num = idx_in_diag;
        den = c - idx_in_diag + 1;
    } else {                              // 奇数对角线：分子递减、分母递增
        num = c - idx_in_diag + 1;
        den = idx_in_diag;
    }
    cout << num << '/' << den << '\n';
    return 0;
}