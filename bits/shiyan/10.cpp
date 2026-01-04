#include <iostream>
#include <vector>
using namespace std;
double fin (int n , int x ,vector<double>& dig){
    if(dig[n] != 1e100) return dig[n];
    if(n == 0) return dig[0] = 1;
    if(n == 1) return dig[1] = x;
    else  return ((2*n - 1)*fin(n - 1, x , dig) - (n - 1)*fin(n-2, x , dig))/n;
}
int main (){
    int n , x;
    cin >> n >> x;
    vector<double> dig(n + 1 ,1e100);
    cout << fin(n , x , dig);
    return 0;
}