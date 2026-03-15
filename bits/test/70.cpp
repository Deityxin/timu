#include <iostream>
#include <algorithm>
#include <vector>
using namespace std ;
int gong(int a , int b){
    while(b != 0){
        int c = b ;
        b = a % b ;
        a = c ;
    }
    return a ;
}
int main (){
    vector<int> lin(3) ;
    for(int i = 0 ; i < 3 ; i++){
        cin >> lin[i] ;
    }
    sort(lin.begin() , lin.end()) ;
    int g = gong(lin[2] , lin[0]) ;
    cout << lin[0] / g << "/" << lin[2] / g << endl ;
    return 0 ;
}