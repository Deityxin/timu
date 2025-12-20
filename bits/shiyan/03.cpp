#include <iostream>
using namespace std; 
void frontn (){
    for (int i = 1 ; i<=4 ;i ++){
            int count = 2*i - 1;
            cout << string(count, '*') << endl;
}
}
int main () {
    int n ;
    cin >> n ;
    if (n > 0&&n < 5){
        frontn();
        }
    else{
        frontn() ;
       for (int i = 5; i <= n; ++i) {
            cout << string(3, '*') << endl;
        }
    }
    return 0;
}