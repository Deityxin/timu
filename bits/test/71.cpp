#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    vector<int> v = {a, b, c};
    sort(v.begin(), v.end());

    string ord;
    cin >> ord; 

    for (int i = 0; i < 3; i++) {
        if (i) cout << ' ';
        cout << v[ord[i] - 'A'];
    }
    cout << '\n';
    return 0;
}