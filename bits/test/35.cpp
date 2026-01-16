#include <bits/stdc++.h>
using namespace std;
long long merge_count(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = l + (r - l) / 2;
    long long inv = merge_count(a, tmp, l, m) + merge_count(a, tmp, m, r);

    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            inv += (m - i);
        }
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; ++t) a[t] = tmp[t];

    return inv;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> tmp(n);
    long long inv = merge_count(a, tmp, 0, n);

    cout << inv;
    return 0;
}