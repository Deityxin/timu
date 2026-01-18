#include <iostream>
using namespace std ;
int main (){
    int a , b , c , d ;
    cin >> a >> b >> c >> d ;
    int a1 = 60 * a ;
    int c1 = 60 * c ;
    int to1 = a1 + b ;
    int to2 = c1 + d ;
    int fin = to2 - to1 ;
    if(fin < 60) cout << "0 " << fin ;
    else if(fin % 60 == 0) cout << static_cast<int>(fin / 60) <<" " << "00" ;
    else cout << static_cast<int>(fin / 60) << " " << fin % 60 ;
    return 0 ;
}