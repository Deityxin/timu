#include <bits/stdc++.h>
using namespace std;
int main() {
    string pat, text;
    if (!getline(cin, pat)) return 0;
    if (!getline(cin, text)) return 0;

    for (char &ch : pat) ch = tolower(static_cast<unsigned char>(ch));
    for (char &ch : text) ch = tolower(static_cast<unsigned char>(ch));

    int n = pat.size();
    int cnt = 0, first = -1;
    int i = 0;
    while (i < (int)text.size()) {
        while (i < (int)text.size() && text[i] == ' ') ++i;
        if (i >= (int)text.size()) break;
        int start = i;
        while (i < (int)text.size() && text[i] != ' ') ++i;
        int len = i - start;
        if (len == n && text.compare(start, n, pat) == 0) {
            if (cnt == 0) first = start;
            ++cnt;
        }
    }
    if (cnt == 0) cout << -1;
    else cout << cnt << ' ' << first;
    return 0;
}