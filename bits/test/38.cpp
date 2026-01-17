#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;
int main(){
    int n , m , b = 0 ;
    cin >> n >> m ;
    int a = m * 3 / 2 ;
    vector<vector<int>> dig( n , vector<int>(2)) ;
    for(int i = 0 ; i < n ; i++) cin >> dig[i][0] >> dig[i][1] ;
    auto compare_ = [](const vector<int>& dig1 , const vector<int>& dig2){
        if(dig1[1] == dig2[1]){
            return dig1[0] < dig2[0] ;
        }
        else{
            return dig1[1] > dig2[1] ;
        }
    } ;
    sort(dig.begin() , dig.end() , compare_) ;
    for(int i = 0 ; i < n ; i++) if(dig[i][1] >= dig[a - 1][1]) b +=1 ;
    cout << dig[a - 1][1] << " " << b << "\n" ;
    for(int i = 0 ; i < b ; i++) cout << dig[i][0] << " " << dig [i][1] << "\n";
    return 0 ;
}