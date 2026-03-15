#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std ;

bool isPrime(int x){
    if(x < 2) return false ;
    if(x == 2 || x == 3) return true ;
    if(x % 2 == 0 || x % 3 == 0) return false ;

    for(int i = 5 ; 1LL * i * i <= x ; i += 6){
        if(x % i == 0 || x % (i + 2) == 0) return false ;
    }
    return true ;
}

int makePal(int x){
    int y = x / 10 ;
    while(y > 0){
        x = x * 10 + y % 10 ;
        y /= 10 ;
    }
    return x ;
}

int main (){
    int a , b ;
    cin >> a >> b ;

    vector<int> ans ;

    if(a <= 11 && 11 <= b) ans.push_back(11) ;

    for(int i = 1 ; ; i++){
        int p = makePal(i) ;
        if(p > b) break ; 
        if(p >= a && isPrime(p)){
            ans.push_back(p) ;
        }
    }

    sort(ans.begin() , ans.end()) ;

    for(int x : ans){
        cout << x << '\n' ;
    }

    return 0 ;
}