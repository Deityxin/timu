#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;

    long long sum = 0;
    int day = x; // 1~7

    for (int i = 0; i < n; i++) {
        if (day >= 1 && day <= 5) sum += 250; // 周一到周五游
        day++;
        if (day == 8) day = 1; // 星期循环
    }

    cout << sum << '\n';
    return 0;
}