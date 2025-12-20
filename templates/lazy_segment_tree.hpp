#pragma once
#include <bits/stdc++.h>
using namespace std;

// 区间加 + 区间求和（迭代写法，0-indexed，构造时传入 n 或 build(vec)）
struct LazySegTree {
    int n; 
    struct Node { long long sum=0, lazy=0; };
    vector<Node> st;
    LazySegTree(int n=0){init(n);} 
    void init(int n_){ n=1; while(n<n_) n<<=1; st.assign(2*n, {}); }
    void build(const vector<long long>& a){ init((int)a.size()); for(int i=0;i<(int)a.size();++i) st[n+i].sum=a[i]; for(int i=n-1;i>0;--i) pull(i); }
    inline void pull(int p){ st[p].sum = st[p<<1].sum + st[p<<1|1].sum; }
    inline void apply(int p, long long v, int len){ st[p].sum += v * len; st[p].lazy += v; }
    inline void push(int p, int l_len, int r_len){ long long v=st[p].lazy; if(!v) return; apply(p<<1, v, l_len); apply(p<<1|1, v, r_len); st[p].lazy=0; }
    void rangeAdd(int l,int r,long long val){ rangeAdd(1,0,n-1,l,r,val); }
    long long rangeSum(int l,int r){ return rangeSum(1,0,n-1,l,r); }
    void rangeAdd(int p,int l,int r,int ql,int qr,long long val){ if(ql>r||qr<l) return; if(ql<=l&&r<=qr){ apply(p,val,r-l+1); return;} int m=(l+r)>>1; push(p,m-l+1,r-m); rangeAdd(p<<1,l,m,ql,qr,val); rangeAdd(p<<1|1,m+1,r,ql,qr,val); pull(p);
    }
    long long rangeSum(int p,int l,int r,int ql,int qr){ if(ql>r||qr<l) return 0; if(ql<=l&&r<=qr) return st[p].sum; int m=(l+r)>>1; push(p,m-l+1,r-m); return rangeSum(p<<1,l,m,ql,qr)+rangeSum(p<<1|1,m+1,r,ql,qr); }
};
