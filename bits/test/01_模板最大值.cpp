#include <iostream>
using namespace std;
template <class T>
T get_max(T a[], int n) {
    T ans = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > ans) ans = a[i];
    }
    return ans;
}
int main() {
    int n;
    cin >> n;
    int a[1000];
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << get_max(a, n) << endl;
    return 0;
}
