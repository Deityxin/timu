#pragma once
#include <bits/stdc++.h>
using namespace std;

static inline long long mul_mod(long long a, long long b, long long mod){
    unsigned long long ua = (a%mod + mod)%mod;
    unsigned long long ub = (b%mod + mod)%mod;
    const unsigned long long m = (unsigned long long)mod;
    unsigned long long r = 0;
    while(ub){
        if(ub & 1){
            if(r >= m - ua) r = r - (m - ua); else r += ua;
        }
        ub >>= 1;
        if(ua >= m - ua) ua = ua - (m - ua); else ua += ua;
    }
    return (long long)r;
}

long long mod_pow(long long a, long long e, long long mod){
    if(mod==1) return 0;
    assert(mod>0);
    assert(e>=0);
    long long r=1%mod; a%=mod; if(a<0) a+=mod;
    while(e){ if(e&1) r=mul_mod(r,a,mod); a=mul_mod(a,a,mod); e>>=1; }
    return r;
}
