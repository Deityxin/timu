#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    string s0;
    getline(cin , s0);
    vector<string> s;
    s.push_back(s0);
    for(int i = 1 ; i < s0.size() ;i++){
        string s2;
        getline(cin , s2);
        s.push_back(s2);
    }
    string fin;
    int n = s0.size();
    cout << n << ' ';
    int ans = 1;
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            fin.push_back(s[i][j]);
        }
    }
    vector<int> fin1;
    if(fin[0] != '0' && fin[0] == fin[1]) cout << 0 << ' ';
    for(int i = 0; i < n * n - 1 ; i++){
        if(fin[i] == fin[i + 1]) ans++;
        else{
            cout << ans << ' ';
            ans = 1;
        }
    }
    cout << ans;
    return 0;
}
    