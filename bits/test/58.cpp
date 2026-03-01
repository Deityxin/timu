#include <bits/stdc++.h>
using namespace std ;
int main (){
    string a , b , res ;
    cin >> a >> b ;
    int i = a.size() - 1 ;
    int j = b.size() - 1 ;
    int carry = 0 ;
    while(i >= 0 || j >= 0 || carry){
        int d1 = (i >= 0) ? a[i--]-'0' : 0 ;
        int d2 = (j >= 0) ? b[j--]-'0' : 0 ;
        int sum = d1 + d2 + carry ;
        carry = sum / 10 ;
        res.push_back('0' + (sum % 10)) ;
    }
    reverse(res.begin(), res.end()) ;
    size_t pos = res.find_first_not_of('0') ;
    if (pos == string::npos) {
        res = "0" ; 
    } else {
        res = res.substr(pos) ; 
    }
    cout << res << endl ;
    return 0 ;
}