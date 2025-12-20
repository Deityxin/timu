#pragma once
#include <bits/stdc++.h>
using namespace std;

// 快速 IO 与常用别名
static struct FastIO { FastIO(){ ios::sync_with_stdio(false); cin.tie(nullptr); } } fastio;
using ll = long long; using pii = pair<int,int>; using pll = pair<long long,long long>;

template<class T> inline void chmax(T& a, const T& b){ if(a<b) a=b; }
template<class T> inline void chmin(T& a, const T& b){ if(b<a) a=b; }
