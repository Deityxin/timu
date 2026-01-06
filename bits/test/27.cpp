#include <iostream>
#include <vector>
using namespace std;
int xun (int n , const vector<vector<int>> &dig , int a , int b){
    for (int i = n - 1 ; i >= 0 ; i--){
        if(dig[i][0] <= a && (dig[i][0] + dig[i][2]) >= a &&
           dig[i][1] <= b && (dig[i][1] + dig[i][3]) >= b) return i + 1;
    }
    return -1;
}
int main (){
    int n ;
    cin >> n;
    vector<vector<int>> dig( n , vector<int>(4));
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < 4 ; j++){
            int x ;
            cin >> x;
            dig[i][j] = x;
        }
    }
    int a , b;
    cin >> a >> b;
    cout << xun( n , dig , a , b);
    return 0;
}