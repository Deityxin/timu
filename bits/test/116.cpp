#include <iostream>
using namespace std;
int main() {
    int n;
    if (!(cin >> n)) return 0; 
    int cnt = 0; 
    int val = 0;  
    int len;      
    while (cnt < n * n && cin >> len) {
        for (int k = 0; k < len; k++) {
            cout << val;
            cnt++;
            if (cnt % n == 0) {
                cout << "\n"; 
            }
        }
        val = 1 - val; 
    }
    return 0;
}