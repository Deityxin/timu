#include <iostream>
using namespace std;
int fin (int a , int b){
    if(b == 0) return a;
    else return fin(b , a % b);
}
int main  (){
    int a , b;
    cin >> a >> b;//a 大于 b
    cout << fin(a , b);
    return 0;
}