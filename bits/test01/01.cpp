#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <class T>
bool panduan (T& a){
    bool temp = false;
    string s = to_string(a);
    for(int i = 0; i < static_cast<int>(s.size()) / 2 ; i++){
        if(s[i] != s[s.size() - 1 - i]) return temp;
    }
    return temp = true;
}
bool panduan(const string& s) {
    for (int i = 0; i < static_cast<int>(s.size()) / 2; ++i) {
        if (s[i] != s[s.size() - 1 - i]) return false;
    }
    return true;
}
int main(){

}