#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    string s;
    cin >> q >> s;
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            string str;
            cin >> str;
            s += str;
            cout << s << '\n';
        } else if (op == 2) {
            int a, b;
            cin >> a >> b;
            s = s.substr(a, b);
            cout << s << '\n';
        } else if (op == 3) {
            int a;
            string str;
            cin >> a >> str;
            s = s.substr(0, a) + str + s.substr(a);
            cout << s << '\n';
        } else if (op == 4) {
            string str;
            cin >> str;
            size_t pos = s.find(str);
            if (pos == string::npos) {
                cout << -1 << '\n';
            } else {
                cout << pos << '\n';
            }
        }
    }
    return 0;
}