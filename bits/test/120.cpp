#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main(){
    int a;
    cin >> a;
    string s;
    cin.ignore();
    getline(cin , s);
    for(char &c: s){
        c = (c - 'a' + a) % 26 + 'a';
    }
    cout << s;
    return 0;
}