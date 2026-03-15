#include <iostream>
using namespace std ;
int main (){
    int n ; 
    int a = 1 ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ;
    cin >> n ;
    while(n != 1){
        int temp = n / 2 ;
        n = temp ;
        a += 1 ;
        if(n == 1){
            break ;
        }
    }
    cout << a << endl ;
    return 0 ;
}