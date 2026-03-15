#include <iostream>
using namespace std ;
int main (){
    int a , c , b;
    cin >> a >> c ;
    if(a % 4 == 0 && a % 100 != 0){
        b = 1 ;
    }else if(a % 100 == 0 && a % 400 == 0){
        b = 1 ;
    }else b = 0 ;
    if(b == 1){
        if(c == 2) cout << "29" ;
        else if(c == 1 || c == 3 || c == 5 || c == 7 || c == 8 || c == 10 || c == 12) cout << "31" ;
        else cout << "30" ;
    }else{
        if(c == 2) cout << "28" ;
        else if(c == 1 || c == 3 || c == 5 || c == 7 || c == 8 || c == 12) cout << "31" ;
        else cout << "30" ;
    }
    return 0 ;
}