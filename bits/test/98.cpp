#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n >> s;
    const string d[10][5] = {
        {"XXX", "X.X", "X.X", "X.X", "XXX"}, // 0
        {"..X", "..X", "..X", "..X", "..X"}, // 1
        {"XXX", "..X", "XXX", "X..", "XXX"}, // 2
        {"XXX", "..X", "XXX", "..X", "XXX"}, // 3
        {"X.X", "X.X", "XXX", "..X", "..X"}, // 4
        {"XXX", "X..", "XXX", "..X", "XXX"}, // 5
        {"XXX", "X..", "XXX", "X.X", "XXX"}, // 6
        {"XXX", "..X", "..X", "..X", "..X"}, // 7
        {"XXX", "X.X", "XXX", "X.X", "XXX"}, // 8
        {"XXX", "X.X", "XXX", "..X", "XXX"}  // 9
    };
    for (int row = 0; row < 5; ++row) {
        for (int i = 0; i < n; ++i) {
            int x = s[i] - '0';
            cout << d[x][row];
            if (i != n - 1) cout << '.';
        }
        cout << '\n';
    }
    return 0;
}