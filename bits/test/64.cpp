#include <iostream>
#include <algorithm>
#include <vector>
using namespace std ;
int main (){
    vector<int> a ;
    for(int i = 0 ; i < 3 ; i++){
        int b ;
        cin >> b ;
        a.push_back(b) ;
    }
    sort(a.begin() , a.end()) ;
    for(int i = 0 ; i < 3 ; i++){
        cout << a[i] << " " ;
    }
    return 0 ;
}