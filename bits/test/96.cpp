#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> lit(n + 1, vector<bool>(n + 1, false));

    auto mark = [&](int x, int y) {
        if (x >= 1 && x <= n && y >= 1 && y <= n) {
            lit[x][y] = true;
        }
    };

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (abs(dx) + abs(dy) <= 2) {
                    mark(x + dx, y + dy);
                }
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                mark(x + dx, y + dy);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!lit[i][j]) {
                ans++;
            }
        }
    }

    cout << ans;
    return 0;
}