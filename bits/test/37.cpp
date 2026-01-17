#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;
int main (){
    int n ;
    cin >> n ;
    vector<int> dig(n) ;
    for(int i = 0 ; i < n ; i++ ) cin >> dig[i] ;
    sort(dig.begin() , dig.end()) ;
    auto new_dig = unique(dig.begin() , dig.end()) ;
    dig.erase(new_dig , dig.end()) ;
    cout << dig.size() << "\n" ;
    for(int a : dig) cout << a << " " ;
    return 0 ;
}