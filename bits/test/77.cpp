#include <iostream>
#include <vector>
using namespace std ;
int main (){
    int n ;
    cin >> n ;
    vector<int> sum ;
    int lin = 0 ;
    for(int i = 1 ; i <= n ; i++){
        sum.push_back(i) ;
    }
    for(int a : sum){
        lin += a ; 
    }
    cout << lin  ;
    return 0 ;
}