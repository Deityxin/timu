#include <iostream>
#include <cmath>
using namespace std ;
int main (){
    double a , b , c ;
    cin >> a >> b >> c ;
    double d = ( a + b + c) / 2.0 ;
    double area = d * (d - a) * (d - b) * (d - c) ;
    printf("%.1f" , sqrt(area)) ;
    return 0 ;
}