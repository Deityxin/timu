#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;
int main (){
    int a ;
    cin >> a ;
    vector<int> lin(a) ;
    for (int i = 0 ; i < a ; i++){
        cin >> lin[i] ;
    }
    sort(lin.begin() , lin.end()) ;
    cout << lin[0] ;
    return 0 ;
}