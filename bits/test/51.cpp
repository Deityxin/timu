#include <iostream>
using namespace std ;
int main (){
    int h , r ;
    cin >> h >> r ;
    double pi = 3.14 ;
    double volume = pi * r * r * h ;
    double h1 = 20 * 1000 ;
    cout << static_cast<int>((h1 / volume) + 1) ;
    return 0 ;
}