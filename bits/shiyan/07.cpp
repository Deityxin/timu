#include <iostream>
#include <sstream>
using namespace std;

int main() {
    istringstream in("1 2");
    int x, y; in >> x >> y;
    cout << (x + y) << '\n';
    return 0;
}