#include <iostream>
#include <cctype>
using namespace std ;
int main() {
    char a_ ;
    cin >> a_ ;
    cout << static_cast<char>(toupper(a_));
    return 0 ;
}