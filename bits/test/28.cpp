#include <iostream>
#include <vector>
using namespace std;
int main (){
    int n;
    cin >> n;
    vector<int> dig(n + 1);
    for (int i = 0; i <= n; i++){
        cin >> dig[i];
    }
    bool first = true;
    for (int i = 0; i <= n; i++){
        int c = dig[i];
        if (c == 0) continue;
        int exp = n - i;
        if (!first && c > 0) cout << "+";
        if (exp == 0){
            cout << c;
        } else {
            if (c == -1) cout << "-";
            else if (c != 1) cout << c;
            cout << "x";
            if (exp != 1) cout << "^" << exp;
        }
        first = false;
    }
    if (first) cout << 0; 
    return 0;
}