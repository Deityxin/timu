#include <iostream>
using namespace std ;
int main (){
    int a ;
    cin >> a ;
    double b ;
    cin >> b ;
    double b1 = b * b ;
    double c = a / b1 ;
    if(c < 18.5){
        cout << "Underweight" ;
    }else if(c >= 18.5 && c < 24) cout << "Normal" ;
    else if(c >= 24) cout << c << '\n' << "Overweight" ;
    return 0 ;
}