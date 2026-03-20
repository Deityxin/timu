#include <bits/stdc++.h>
using namespace std;
int main() {
    int w, x, h;
    cin >> w >> x >> h;
    int q;
    cin >> q;
    vector<vector<vector<int>>> alive(
        w + 1, vector<vector<int>>(x + 1, vector<int>(h + 1, 1)));
    for (int t = 0; t < q; t++) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int k = z1; k <= z2; k++) {
                    alive[i][j][k] = 0;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= x; j++) {
            for (int k = 1; k <= h; k++) {
                ans += alive[i][j][k];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}