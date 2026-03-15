#include <iostream>
#include <iomanip>
#include <vector>
using namespace std ;
int main (){
    int n , k ;
    cin >> n >> k ;
    vector<int> shu ;
    for(int i = 1 ; i <= n ; i++){
        shu.push_back(i) ;
    }
    int num = 0 , num1 = 0 , num2 = 0 , num3 = 0 ;
    for(int i = 0 ; i < shu.size() ; i++){
        if(shu[i] % k == 0 ){
            num += 1 ;
            num1 += shu[i] ;
        }else{
            num2 += 1 ;
            num3 += shu[i] ;
        }
    }
    double a = static_cast<double>(num1) / num ;
    double b = static_cast<double>(num3) / num2 ;
    cout << fixed << setprecision(1) << a << " " << fixed << setprecision(1) << b << endl ;
    return 0 ; 
}