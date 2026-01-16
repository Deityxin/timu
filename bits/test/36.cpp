#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;
int main (){
    int N ;
    cin >> N ;
    vector<int> dig(N) ; 
    for (int i = 0 ; i < N ; i++ ) cin >> dig[i] ;
    sort(dig.begin() , dig.end()) ;
    for(int a : dig) cout << a << " " ; 
    return 0 ;
}