#include <iostream>
using namespace std;
template <class T>
T my_max(T a, T b) {
    return a > b ? a : b;
}
template <class T>
T my_min(T a, T b) {
    return a < b ? a : b;
}
int main() {
    int a, b;
    cin >> a >> b;
    cout << my_max(a, b) << endl;
    cout << my_min(a, b) << endl;
    return 0;
}
