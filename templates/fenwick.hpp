#pragma once
#include <bits/stdc++.h>
using namespace std;

// 1-indexed Fenwick Tree (Binary Indexed Tree)
struct Fenwick {
    int n; vector<long long> bit;
    Fenwick(int n=0){init(n);} 
    void init(int n_){ n=n_; bit.assign(n+1,0); }
    void add(int idx, long long delta){ for(; idx<=n; idx+=idx&-idx) bit[idx]+=delta; }
    long long sum(int idx){ long long r=0; for(; idx>0; idx-=idx&-idx) r+=bit[idx]; return r; }
    long long rangeSum(int l,int r){ if(r<l) return 0; return sum(r)-sum(l-1);} 
};
