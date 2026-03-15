#include <iostream>
using namespace std;
int main (){
    double a;
    cin >> a;
    double b = 2.00;
    double sum = 0.0;
    int shu = 0;

    while(sum < a){
        double temp = b;
        b = b * 0.98;
        sum += temp;
        shu += 1;
    }
    cout << shu;
    return 0;
}