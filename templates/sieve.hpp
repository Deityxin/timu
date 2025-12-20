#pragma once
#include <bits/stdc++.h>
using namespace std;

// 线性筛：最小质因子 lp 与质数表 primes
struct LinearSieve {
    int n; vector<int> lp, primes;
    LinearSieve(int n=0){ if(n) init(n); }
    void init(int n_){ n=n_; lp.assign(n+1,0); primes.clear();
        for(int i=2;i<=n;i++){
            if(lp[i]==0){ lp[i]=i; primes.push_back(i); }
            for(int p: primes){ long long v=1LL*p*i; if(v>n || p>lp[i]) break; lp[v]=p; }
        }
    }
};
