#include <iostream>
#include <vector>
#include <string>
using namespace std;
int lookfor (vector<vector<string>> &s ,vector<vector<int>> &dig , int m){
    int j = 0;
    int n = (int)s[0].size();
    for (int i = 0; i < m; i++){
        int face = (s[0][j] == "0") ? 0 : 1;
        int a = dig[i][0], step = dig[i][1];
        int delta = (face == a) ? -step : step;
        j = (j + delta) % n;
        if (j < 0) j += n;
    }
    return j;
}

int main (){
    int n , m ;
    cin >> n >> m ;
    vector<vector<string>>  s_(2, vector<string>(n));
    for(int i = 0 ; i < n ; i++){
        int a ; string s_1;
        cin >> a >> s_1 ;
        s_[0][i] = to_string(a) ;
        s_[1][i] = s_1 ;
    }
    vector<vector<int>> dig(m, vector<int>(2));
    for(int j = 0 ; j < m ; j ++){
        cin >> dig[j][0] >> dig[j][1] ;
    }
    cout << s_[1][lookfor(s_ , dig , m)] << endl ;
    return 0 ;
}
// 做之前 先找出确定的规律 然后在进行思考 如何做  不要上来就是暴力枚举 根本做不出来