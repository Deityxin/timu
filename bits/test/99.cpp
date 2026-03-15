#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    int a;
    cin >> a;
    vector<vector<int>> shu(a, vector<int>(3));
    for (auto &s : shu) { 
        cin >> s[0] >> s[1] >> s[2];
    }
    int ans = 0;
    for (int i = 0; i < a; i++) {
        for (int j = i + 1; j < a; j++) { 
            int sum_i = shu[i][0] + shu[i][1] + shu[i][2];
            int sum_j = shu[j][0] + shu[j][1] + shu[j][2];
            if (abs(shu[i][0] - shu[j][0]) <= 5 &&
                abs(shu[i][1] - shu[j][1]) <= 5 &&
                abs(shu[i][2] - shu[j][2]) <= 5 &&
                abs(sum_i - sum_j) <= 10) {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}