#include <iostream>
using namespace std;
int main (){
    long long  a , b , c;
    cin >> a >> b >> c;
    long  d = b - a ;
    long long fin = d * (c - 1) + a;
    long long fin1 =  ((a + fin) * c) / 2;
    cout << fin1 ;
    return 0;
}