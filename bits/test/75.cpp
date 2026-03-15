#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int cur = 1;
    for (int row = 1; row <= n; ++row) {
        int len = n - row + 1;
        for (int j = 0; j < len; ++j) {
            cout << setw(2) << setfill('0') << cur;
            ++cur;
        }
        cout << '\n';
    }
    return 0;
}