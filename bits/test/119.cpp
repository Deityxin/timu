#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main(){
    string s;
    getline(cin , s);
    for(char &c: s) c = toupper(c);
    cout << s;
    return 0;
}