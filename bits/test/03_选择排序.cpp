#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n - 1; ++i) {
        int pos = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[pos]) pos = j;
        }
        if (pos != i) swap(a[i], a[pos]);
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;
    return 0;
}