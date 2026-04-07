#include <iostream>
using namespace std;
using i128 = __int128_t;
void print_i128(i128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    string s;
    while (x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    for (int i = (int)s.size() - 1; i >= 0; --i) cout << s[i];
}
int main() {
    long long sum = 0;
    int cnt = 0;
    int x;
    while (cin >> x) {
        sum += x;
        ++cnt;
    }
    i128 ans = 0;
    if (cnt > 0) {
        i128 mul = 1;
        for (int i = 1; i < cnt; ++i) {
            mul *= 2;
        }
        ans = (i128)sum * mul;
    }
    print_i128(ans);
    cout << '\n';
    return 0;
}