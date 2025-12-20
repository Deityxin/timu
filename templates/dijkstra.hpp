#pragma once
#include <bits/stdc++.h>
using namespace std;

// 图用邻接表：vector<vector<pair<int,int>>> g; // u -> (v, w)
vector<long long> dijkstra(int n, const vector<vector<pair<int,int>>>& g, int s){
    const long long INF = (1LL<<62);
    vector<long long> dist(n, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    dist[s]=0; pq.push({0,s});
    while(!pq.empty()){
        auto [du,u]=pq.top(); pq.pop();
        if(du!=dist[u]) continue;
        for(auto [v,w]: g[u]) if(dist[v] > du + w){
            dist[v] = du + w; pq.push({dist[v], v});
        }
    }
    return dist;
}
