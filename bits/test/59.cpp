#include <bits/stdc++.h>
using namespace std ;
int main (){
    string a , b ;
    cin >> a >> b ;
    vector<int> A , B;
    for(int i = a.size() - 1 ; i >= 0 ; i--){
        A.push_back(a[i] - '0') ;
    }
    for(int i = b.size() - 1 ; i >= 0 ; i--){
        B.push_back(b[i] - '0') ;
    }
    vector<int> C (A.size() + B.size() , 0) ;
    for (int i = 0 ; i < (int)A.size() ; i++) {
        for (int j = 0 ; j < (int)B.size() ; j++) {
            C[i + j] += A[i] * B[j] ;
        }
    }
    int carry = 0 ;
    for (int k = 0 ; k < (int)C.size() ; k++) {
        int temp = C[k] + carry ;  // 当前位值 + 低位的进位
        C[k] = temp % 10 ;         // 保留个位
        carry = temp / 10 ;        // 计算向高位的进位
    }
    while (carry) {
        C.push_back(carry % 10) ;
        carry /= 10 ;
    }
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back() ;
    }
    reverse(C.begin(), C.end());
    for (int digit : C) {
        cout << digit;
    }
    return 0;
}
