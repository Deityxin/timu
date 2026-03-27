#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> add(vector<int> &a,vector<int> &b){
    if(a.size() < b.size()) return add(b , a);
    int t = 0;
    vector<int> c;
    for(int i = 0; i < a.size() ; i++){
        t += a[i];
        if(i < b.size()) t = t + b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if(t) c.push_back(t);
    return c;
}
int main(){
    int n;
    cin >> n;
    vector<vector<int>> tem(n + 1);
    tem[1] = {1};
    if (n >= 2) tem[2] = {2};
    for(int i = 3 ; i <= n ; i++){
        tem[i] = add(tem[i - 2] , tem[i - 1]);
    }
    vector<int> ans = tem[n];
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    return 0;
}