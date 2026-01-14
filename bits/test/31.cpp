#include <bits/stdc++.h>
using namespace std;
void simulate(const vector<char>& seq, int target) {
    int w = 0, l = 0;
    for (char c : seq) {
        if (c == 'W') ++w;
        else if (c == 'L') ++l;
        if ((w >= target || l >= target) && abs(w - l) >= 2) {
            cout << w << ':' << l << '\n';
            w = l = 0;
        }
    }
    cout << w << ':' << l << '\n';
}

int main() {
    vector<char> seq;
    char ch;
    while (cin >> ch) {
        if (ch == 'E') break;
        if (ch == 'W' || ch == 'L') seq.push_back(ch);
    }
    simulate(seq, 11);
    cout << '\n';
    simulate(seq, 21);
    return 0;
}