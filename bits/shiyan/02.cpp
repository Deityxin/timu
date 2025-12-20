#include <iostream>
using namespace std;
int main () {
    int x ;
    cin >> x;
    if (x < 5){
        int y = x;
        cout << y << endl;
    }else if (x >= 5&& x < 10){
        int y = 3*x+2 ;
        cout << y << endl;
    }else{
        int y = x*x + 3*x - 6 ;
        cout << y << endl;
    }
    return 0 ;
}