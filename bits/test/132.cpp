#include <iostream>
#include <string>
using namespace std;
char lin[] = {
    ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z'
};
int xun(char hui) {
    for (int i = 0; i < 27; i++) {
        if (hui == lin[i]) return i;
    }
    return 1;
}
int main() {
    string hui, xiao;
    cin >> hui >> xiao;
    long long a = 1, b = 1;
    for (char s : hui) a = a * xun(s);
    for (char s : xiao) b = b * xun(s);
    if (a % 47 == b % 47) cout << "GO" << endl;
    else cout << "STAY" << endl;
    return 0;
}