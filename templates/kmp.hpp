#pragma once
#include <bits/stdc++.h>
using namespace std;

vector<int> kmp_prefix(const string& p){
    int m=p.size(); vector<int> pi(m,0);
    for(int i=1;i<m;i++){
        int j=pi[i-1];
        while(j>0 && p[i]!=p[j]) j=pi[j-1];
        if(p[i]==p[j]) j++;
        pi[i]=j;
    }
    return pi;
}
vector<int> kmp_search(const string& s, const string& p){
    if(p.empty()) return {};
    auto pi = kmp_prefix(p); vector<int> occ; int j=0;
    for(int i=0;i<(int)s.size();i++){
        while(j>0 && s[i]!=p[j]) j=pi[j-1];
        if(s[i]==p[j]) j++;
        if(j==(int)p.size()){ occ.push_back(i-j+1); j=pi[j-1]; }
    }
    return occ;
}
