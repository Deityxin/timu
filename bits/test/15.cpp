#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main () {
    string s;
    getline(cin , s);
    int c = 0;
    vector<int> a;
    for (char ch : s){
        if(isdigit(ch))
        a.push_back(ch - '0');
    }
    for (int i = 0; i < 9; i++){
        c += a[i]*(i + 1);
    }
    int d = c % 11;
    char e = (d == 10) ? 'X' : char('0' + d);
    if (e == s.back()){
        cout << "Right" ;
    }else {
        s.back()= e;
        cout << s;
    }
    return 0;
}