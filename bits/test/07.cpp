#include <iostream>
#include <vector>
#include <cmath>
using namespace std ;
int prepare (int a){
    int n = (static_cast<int>((-1 + sqrt(1.0 + 8.0 * a)) / 2.0)) + 1;
    return n;
}
int main () {
    int count;
    cin >> count ;
    int c = prepare(count) ;
    for (int i = 1,j = c ; i <= c;i++ ,j--){
        double c = j/i;
    }
    int finial = (count - c*c/2) - 1 ;
    return 0;
}