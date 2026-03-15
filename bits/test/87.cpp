#include <iostream>
#include <vector>
using namespace std;
bool isPrime(int x){
    if(x < 2) return false ;
    if(x == 2 || x == 3) return true ;
    if(x % 2 == 0 || x % 3 == 0) return false ;
    for(int i = 5 ; 1LL * i * i <= x ; i += 6){
        if(x % i == 0 || x % (i + 2) == 0) return false ;
    }
    return true ;
}
int main (){
    int a ;
    cin >> a;
    vector<int> sum(a);
    for(int i = 0; i < a ; i++) cin >> sum[i];
    for(int s:sum){
        if(isPrime(s)) cout << s << " ";
    }
    return 0;
}