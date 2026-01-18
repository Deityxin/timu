#include <iostream>
#include <string>
using namespace std ;
int main (){
    char c ;
    cin >> c ;
    int a = 3 ;
    for(int i = 0 ; i < 3 ; i++){
        cout << string(a - i - 1 , ' ') << string((i + 1) * 2 -1 , c) << "\n" ;
    }
    return 0 ;
}