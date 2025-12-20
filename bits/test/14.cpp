#include <iostream>
#include <string>
using namespace std;
int main () {
    string c ;
    getline(cin, s);
    size_t count = 0 ;
    for (char ch : s) {
        if (ch != ' ' && ch != '\n') count++;
    }
    cout << count ;
    return 0;
}