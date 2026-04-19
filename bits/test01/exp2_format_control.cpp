#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    int x = 300;
    cout << oct << x << '\n';
    cout << dec << x << '\n';
    cout << hex << x << '\n';
    cout << dec;
    const double pi = 3.1415683;
    cout << fixed << setprecision(6) << pi << '\n';
    cout << fixed << setprecision(8) << pi << '\n';
    cout << scientific << setprecision(6) << pi << '\n';
    cout << fixed << setprecision(6) << pi << '\n';
    return 0;
}
