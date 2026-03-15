#include <iostream>
#include <iomanip>
using namespace std;
int main (){
    int a;
    cin >> a;
    for(int i = 1; i <= a * a; i++){
        cout << setfill('0') << setw(2) << i;
        if(i % a == 0){cout << '\n';}
    }
    cout << '\n';
    int x = 1;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= 2 * (a - i); j++) {
            cout << ' ';
        }
        for (int j = 1; j <= i; j++) {
            cout << setfill('0') << setw(2) << x++;
        }
        cout << '\n';
    }

    return 0;
}