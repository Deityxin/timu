#pragma once
#include <bits/stdc++.h>
using namespace std;

// 静态 RMQ：区间最值查询（O(1) 查询，O(n log n) 预处理）
struct SparseTable {
    int n, K; vector<vector<int>> st; vector<int> lg;
    function<int(int,int)> fn; // 合并函数：min/max/gcd...
    SparseTable(): n(0), K(0) {}
    static int floor_log2_int(int x){
        int k = 0; while((1<<(k+1)) <= x) ++k; return k;
    }
    void build(const vector<int>& a, function<int(int,int)> combine){
        assert(!a.empty());
        n=a.size(); K=floor_log2_int(n)+1; fn=combine; st.assign(K, vector<int>(n)); lg.assign(n+1,0);
        for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
        st[0]=a;
        for(int k=1;k<K;k++) for(int i=0;i+(1<<k)<=n;i++) st[k][i]=fn(st[k-1][i], st[k-1][i+(1<<(k-1))]);
    }
    int query(int l,int r){
        assert(n>0);
        assert(l>=0 && r>=l && r<n);
        assert((bool)fn);
        int k=lg[r-l+1];
        return fn(st[k][l], st[k][r-(1<<k)+1]);
    }
};
