#pragma once
#include <bits/stdc++.h>
using namespace std;

// 简洁版和线段树（支持点更新 + 区间求和）
struct SegTree {
    int n; vector<long long> st;
    SegTree(int n=0){init(n);} 
    void init(int n_){ n=1; while(n<n_) n<<=1; st.assign(2*n,0); }
    void build(const vector<long long>& a){ init((int)a.size()); for(int i=0;i<(int)a.size();++i) st[n+i]=a[i]; for(int i=n-1;i>0;--i) st[i]=st[i<<1]+st[i<<1|1]; }
    void pointAdd(int idx, long long delta){ int p=n+idx; st[p]+=delta; for(p>>=1;p;p>>=1) st[p]=st[p<<1]+st[p<<1|1]; }
    long long query(int l,int r){ // [l,r]
        long long L=0,R=0; l+=n; r+=n; 
        while(l<=r){ if(l&1) L+=st[l++]; if(!(r&1)) R+=st[r--]; l>>=1; r>>=1; }
        return L+R;
    }
};
