#pragma once
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r, sz;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n); r.assign(n, 0); sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        if (r[a] == r[b]) r[a]++;
        return true;
    }
    int size(int x) { return sz[find(x)]; }
};
