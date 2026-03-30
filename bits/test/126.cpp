#include <iostream>
#include <vector>
using namespace std;
int n;
int path[10];
vector<vector<int>> ans;
void dfs(int idex , int sum){
    if(idex == 10){
        if(sum == n) ans.push_back(vector<int>(path , path + 10));
        return;
    }
    int rest = 10 - idex;
    if (sum + rest > n) return;
    if (sum + rest * 3 < n) return;
    for(int x = 1 ; x <= 3; x++){
        path[idex] = x;
        dfs(idex + 1, sum + x);
    }
}
int main(){
    cin >> n;
    if(n < 10) cout << '0';
    dfs(0 , 0);
    cout << ans.size() << '\n';
    for (const auto &v : ans) {
        for (int x : v) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}