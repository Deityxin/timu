#include <iostream>
#include <cmath>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
using namespace std;
double sqrt1(int a){
    if (a < 0) return -1.0;
    if (a == 0) return 0.0;
    const double EPS = 1e-9;
    double x1 = a / 2.0;
    while (true){
        double x2 = 0.5 * (x1 + a / x1);
        if (fabs(x1 - x2) < EPS) break;
        x1 = x2;
    }
    return x1;
}
int main (){
    int a ;
    cin >> a ;
    double c = sqrt1(a);
    cout << c;
    return 0;
}