#include <bits/stdc++.h>
using namespace std;
int main() {
    static int dp[21][21][21];
    for (int a = 0; a <= 20; ++a) {
        for (int b = 0; b <= 20; ++b) {
            for (int c = 0; c <= 20; ++c) {
                if (a == 0 || b == 0 || c == 0) dp[a][b][c] = 1;
                else if (a < b && b < c)
                    dp[a][b][c] = dp[a][b][c - 1] + dp[a][b - 1][c - 1] - dp[a][b - 1][c];
                else
                    dp[a][b][c] = dp[a - 1][b][c] + dp[a - 1][b - 1][c] + dp[a - 1][b][c - 1] - dp[a - 1][b - 1][c - 1];
            }
        }
    }
    vector<array<long long, 3>> qs;
    long long x, y, z;
    while (cin >> x >> y >> z) {
        if (x == -1 && y == -1 && z == -1) break;
        qs.push_back({x, y, z});
    }
    for (auto [ox, oy, oz] : qs) {
        long long x = ox, y = oy, z = oz;
        int ans;
        if (x <= 0 || y <= 0 || z <= 0) {
            ans = 1;
        } else if (x > 20 || y > 20 || z > 20) {
            ans = dp[20][20][20];
        } else {
            ans = dp[(int)x][(int)y][(int)z];
        }
        cout << "w(" << ox << ", " << oy << ", " << oz << ") = " << ans << '\n';
    }
    return 0;
}