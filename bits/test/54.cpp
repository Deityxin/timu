#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main (){
    int t ;
    cin >> t ;
    if(t == 1){
        cout << "I love Luogu!" ;
    }else if(t == 2){
        cout << 6 << " " << 4 ;
    }else if(t == 3){
        int a = 14 / 4 ;
        cout << a << "\n" << a * 4 << "\n" << 14 - a * 4 ;
    }else if(t == 4){
        cout << fixed << setprecision(3) << 500.0 / 3.0 ;
    }else if(t == 5){
        cout << (260 + 220) / (12 + 20) ;
    }else if(t == 6){
        cout << sqrt(6 * 6 + 9 * 9) ;
    }else if(t == 7){
        cout << 110 << "\n" << 90 << "\n" << 0 ;
    }else if(t == 8){
        const double pi = 3.141593 ;
        double r = 5 ;
        cout << fixed << setprecision(6);
        cout << 2 * pi * r << "\n" << pi * r * r << "\n" << 4.0 / 3 * pi * r * r * r ;
    }else if(t == 9){
        cout << 22 ;
    }else if(t == 10){
        cout << 9 ;
    }else if(t == 11){
        cout << fixed << setprecision(3) << 100.0 / (8 - 5) ;
    }else if(t == 12){
        cout << 13 << "\n" << 'R' ;
    }else if(t == 13){
        const double pi = 3.141593 ;
        double v = 4.0 / 3 * pi * (4 * 4 * 4 + 10 * 10 * 10) ;
        cout << static_cast<int>(cbrt(v)) ;
    }else if(t == 14){
        cout << 50 ;
    }
    return 0 ;
}