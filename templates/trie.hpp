#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node{ int nxt[26]; int end=0; Node(){ memset(nxt,-1,sizeof nxt);} };
    vector<Node> t; 
    Trie(){ t.reserve(1<<20); t.push_back(Node()); }
    void insert(const string& s){ int u=0; for(char ch: s){ int c=ch-'a'; if(t[u].nxt[c]==-1){ t[u].nxt[c]=t.size(); t.push_back(Node()); } u=t[u].nxt[c]; } t[u].end++; }
    int countPrefix(const string& s){ int u=0; for(char ch: s){ int c=ch-'a'; if(t[u].nxt[c]==-1) return 0; u=t[u].nxt[c]; } return 1; }
    int countWord(const string& s){ int u=0; for(char ch: s){ int c=ch-'a'; if(t[u].nxt[c]==-1) return 0; u=t[u].nxt[c]; } return t[u].end; }
};
