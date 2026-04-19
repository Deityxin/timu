#include <iostream>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    set<int> ids;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ids.insert(x);
    }
    cout << ids.size() << '\n';
    int cnt = 0;
    for (int x : ids) {
        if (cnt) cout << ' ';
        cout << x;
        cnt++;
    }
    cout << '\n';
    return 0;
}
