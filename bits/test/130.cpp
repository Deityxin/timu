#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void reverse_num(string s) {
    int l = 0, r = s.size() - 1;
    while (l <= r && s[l] == '0') l++;
    while (l <= r && s[r] == '0') r--;
    if (l > r) cout << '0';
    else for (int i = r; i >= l; i--) cout << s[i];
}
int main(){
    string s;
    getline(cin , s);
    if(s.find('/') != string::npos){
        size_t pos = s.find('/');
        reverse_num(s.substr(0, pos));
        cout << '/';
        reverse_num(s.substr(pos + 1));
    }else if (s.find('.') != string::npos) {
        size_t pos = s.find('.');
        reverse_num(s.substr(0, pos));
        cout << '.';
        reverse_num(s.substr(pos + 1));
    } else if (s.back() == '%') {
        reverse_num(s.substr(0, s.size() - 1));
        cout << '%';
    } else {
        reverse_num(s);
    }
    return 0;
}