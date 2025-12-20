#pragma once
#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG; int root; 
    vector<int> depth; 
    vector<vector<int>> up; 
    vector<vector<int>> g;
    LCA(int n=0, int root=0): n(n), root(root) { init(n, root); }
    void init(int n_, int root_){
        n=n_; root=root_;
        LOG = 1; while((1<<LOG) <= n) LOG++;
        g.assign(n, {}); depth.assign(n, 0); up.assign(LOG, vector<int>(n, -1));
    }
    void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }
    void build(){ dfs(root, root); for(int k=1;k<LOG;k++) for(int v=0; v<n; v++) up[k][v] = up[k-1][ up[k-1][v] ]; }
    void dfs(int v,int p){ up[0][v]=p; for(int to: g[v]) if(to!=p){ depth[to]=depth[v]+1; dfs(to,v);} }
    int jump(int v,int k){ for(int i=0;i<LOG;i++) if(k&(1<<i)) v=up[i][v]; return v; }
    int lca(int a,int b){ if(depth[a]<depth[b]) swap(a,b); a=jump(a, depth[a]-depth[b]); if(a==b) return a; for(int k=LOG-1;k>=0;k--) if(up[k][a]!=up[k][b]){ a=up[k][a]; b=up[k][b]; } return up[0][a]; }
};
