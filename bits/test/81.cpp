#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long a = 0, b = 1;
    if (n == 0) {
        cout << fixed << setprecision(2) << 0.0 << '\n';
        return 0;
    }
    if (n == 1) {
        cout << fixed << setprecision(2) << 1.0 << '\n';
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    cout << fixed << setprecision(2) << (double)b << '\n';
    return 0;
}