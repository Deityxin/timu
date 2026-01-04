#include <bits/stdc++.h>
using namespace std;
static long long dp[201][7][201];

long long solve(int sum, int parts, int minVal) {
    if (parts == 1) return 1; 
    long long &memo = dp[sum][parts][minVal];
    if (memo != -1) return memo;

    long long ans = 0;
    int upper = sum / parts;
    for (int x = minVal; x <= upper; ++x) {
        ans += solve(sum - x, parts - 1, x);
    }
    memo = ans;
    return ans;
}

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    memset(dp, -1, sizeof(dp));
    cout << solve(n, k, 1) << "\n";
    return 0;
}