#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a;
    if (!(cin >> a) || a <= 0) return 0;
    long long limit = 6 * a + 2;
    long long prev = 0, curr = 1;
    for (long long k = 1; k <= limit; ++k) {
        long long next = (prev + curr) % a;
        prev = curr;
        curr = next;
        if (prev == 0 && curr == 1) {
            cout << k << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}