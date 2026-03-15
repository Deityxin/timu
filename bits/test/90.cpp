#include <iostream>
using namespace std;
long long jie(int n){
    if(n < 0) return -1;
    if(n == 0) return 1;
    return n*jie(n - 1);   
}
int main (){
    int n;
    cin >> n;
    cout << jie(n) << endl;
    return 0;
}