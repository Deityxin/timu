#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main() {
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    char last_op;
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        stringstream ss(s);
        char op;
        int num1, num2;
        if (s[0] >= 'a' && s[0] <= 'z') {
            ss >> op >> num1 >> num2;
            last_op = op;
        } else {
            op = last_op;
            ss >> num1 >> num2;
        }
        int ans;
        char symbol;
        if (op == 'a') {
            ans = num1 + num2;
            symbol = '+';
        } else if (op == 'b') {
            ans = num1 - num2;
            symbol = '-';
        } else if (op == 'c') {
            ans = num1 * num2;
            symbol = '*';
        }
        string express = to_string(num1) + symbol + to_string(num2) + "=" + to_string(ans);
        cout << express << endl;
        cout << express.length() << endl;
    }
    return 0;
}