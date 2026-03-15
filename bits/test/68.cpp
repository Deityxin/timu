#include <iostream>
#include <iomanip>
using namespace std ;
int main (){
    int a ;
    cin >> a ;
    if(a <= 150){
        double b = a *  0.4463 ;
        cout << fixed << setprecision(1) << b ;
    }else if(a > 150 && a <= 400){
        double b = 0.4663 * (a - 150) + 150 * 0.4463 ;
        cout << fixed << setprecision(1) << b ;
    }else{
        double b = 0.5663 * (a - 400) + 150 * 0.4463 + 250 * 0.4663 ;
        cout << fixed << setprecision(1) << b ;
    }
    return 0 ;
}