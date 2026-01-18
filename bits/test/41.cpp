#include <bits/stdc++.h>
using namespace std ;
int main() {
    for (int i = 1; i <= 3; ++i) {
        cout << string(3 - i, ' ') << string(2 * i - 1, '*') << "\n" ;
    }
    for (int i = 2; i >= 1; --i) {
        cout << string(3 - i, ' ') << string(2 * i - 1, '*') << "\n" ;
    }
    return 0;
}