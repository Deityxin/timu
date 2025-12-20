#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> prepare (vector<int> num){
    sort(num.begin(), num.end());
    return num;
}
int main (){
    int n , m , k;
    cin >> n >> m >> k;
    vector<vector<int>> pre(n,vector<int>(m));
    vector<int> numk ,fin(n, 0),fin1;
    vector<vector<int>> prel(m,vector<int>(n,0));
    vector<vector<int>> day(k + 1);
    for(int i = 1;i <= k; i++){
        numk.push_back(i);
    }
    for(int j = 0;j < n; j++){
        for(int k = 0; k < m; k++){
            cin >> pre[j][k];
        }
    }
   for(int b = 0;b < m ;b++){
    for(int c = 0; c < n ; c++){
        vector<int> temporary;
        temporary.push_back(pre[c][b]);
        prepare(temporary);
        bool found = false;
        for (int num : numk) {
            if (find(temporary.begin(), temporary.end(), num) != temporary.end()) {
                found = true;
                break; 
            }
        }
        prel[b][c] = found ? 1 : 0;
        day[pre[c][b]].push_back(b + 1); 
    }
   }
   for (int d = 1; d <= k; d++){     
       vector<int> seen(m + 1, 0);
       int f = 0;
       for (int paper : day[d]) {
           if (!seen[paper]) { seen[paper] = 1; f++; }
       }
       fin1.push_back(f);
   }
   for (int i = 0; i < fin1.size(); i++) {
       if (i) cout << ' ';
       cout << fin1[i];
   }
   cout << '\n';
    return 0;
}