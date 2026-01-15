#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;
int main () {
    int N ; 
    cin >> N ;
    if (N <= 0 || (N & 1) == 0) return 0; // 仅支持奇数阶
    vector<vector<int>> dig(N , vector<int>(N , 0)) ;
    int a = (N / 2) ;
    dig[0][a] = 1 ;
    int k = a , j = 0 ;// j是行数 k 是列数
    for(int i = 1 ; i <= (N * N) - 1 ; i++){
        if(j == 0 && k != N - 1) dig[N - 1][k + 1] = i + 1 , j = N - 1 , k = k + 1;
        else if(k == N - 1 && j != 0 ) dig[j - 1][0] = i + 1, j = j - 1 , k = 0;
        else if(j == 0 && k == N - 1) dig[j + 1][k] = i + 1 , j = j + 1 ;
        else if(j != 0 && k != N - 1 ){
            if(dig [j - 1][ k + 1] == 0) {dig[j - 1][k + 1] = i + 1 , j = j - 1, k = k + 1 ;}
            else {
                int nj = (j + 1 == N) ? 0 : j + 1;
                dig[nj][k] = i + 1 ; j = nj ;
            }
        }
    }
    for(const auto& row : dig) {
        for(int val : row) {
            cout << val <<" ";
        }
        cout << endl;
    }
    return 0 ;
}