#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std ;
int main (){
    int a ;
    cin >> a ;

    vector<int> a1 = {1} ;   // 当前 i!
    vector<int> sum = {0} ;  // 1!+2!+...+n!

    for(int i = 1 ; i <= a ; i++){
        int carry = 0 ;
        for(int j = 0 ; j < (int)a1.size() ; j++){
            long long lin = 1LL * a1[j] * i + carry ;
            a1[j] = (int)(lin % 10000) ;
            carry = (int)(lin / 10000) ;
        }
        while(carry > 0){
            a1.push_back(carry % 10000) ;
            carry /= 10000 ;
        }

        // sum += a1
        if(sum.size() < a1.size()) sum.resize(a1.size(), 0) ;
        carry = 0 ;
        for(int j = 0 ; j < (int)sum.size() ; j++){
            int v = sum[j] + carry + (j < (int)a1.size() ? a1[j] : 0) ;
            sum[j] = v % 10000 ;
            carry = v / 10000 ;
        }
        while(carry > 0){
            sum.push_back(carry % 10000) ;
            carry /= 10000 ;
        }
    }

    cout << sum.back() ;
    for(int i = (int)sum.size() - 2 ; i >= 0 ; i--){
        cout << setw(4) << setfill('0') << sum[i] ;
    }
    return 0 ;
}// 对于高精度 可以设置万进制 每次取后四个数字 然后在输出的时候  取数组中最后一位 然后使用setw（4）  来控制 输出格式