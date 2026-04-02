#include <bits/stdc++.h>
using namespace std;
string s;
int val[3];
int id(char c) {
    return c - 'a';
}
void solve(int pos) {
    int left = id(s[pos]);
    char right = s[pos + 3];
    if (right >= '0' && right <= '9') val[left] = right - '0';
    else val[left] = val[id(right)];
    if (pos + 5 < (int)s.size()) solve(pos + 5);
}
int main() {
    cin >> s;
    solve(0);
    cout << val[0] << ' ' << val[1] << ' ' << val[2] << '\n';
    return 0;
}