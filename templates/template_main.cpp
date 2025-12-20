#include <bits/stdc++.h>
#include "common.hpp"
// #include "fast_pow.hpp"
// #include "dsu.hpp"
// #include "fenwick.hpp"
// #include "segment_tree.hpp"
// #include "dijkstra.hpp"
// #include "kmp.hpp"
// #include "lca.hpp"
// #include "sieve.hpp"
using namespace std;

int main(){
    // FastIO 已在 common.hpp 中启用
    int n; if(!(cin >> n)) return 0; // 示例：读一个数
    vector<int> a(n); for(int i=0;i<n;i++) cin >> a[i];
    cout << accumulate(a.begin(), a.end(), 0LL) << "\n";
    return 0;
}
