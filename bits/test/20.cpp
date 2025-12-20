#include <iostream>
#include <vector>
using namespace std;
vector <int> digit_;
int legal  (int n) {
    if(n == 1) return 1;
    if(digit_[n] != 0) return digit_[n];
    int count = 1;
    for (int i = 1; i <= n / 2;i++){
        count += legal(i);
    }
    digit_[n] = count;
    return count;
}
int main (){
    int n ;
    cin >> n;
    digit_.resize(n+1,0);
    int m = legal(n);
    cout << m ;
    return 0;
}