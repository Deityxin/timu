#include <iostream>
 #include <vector>
 #include <cmath>
 #include <iomanip>
 using namespace std;
 double a1 (int a , int b , int c , int d){
    double e = sqrt((static_cast<double>(a) - c) * (static_cast<double>(a) - c) +
                    (static_cast<double>(b) - d) * (static_cast<double>(b) - d) );
    return e;    
 }
 int main(){
    vector<int> sum(6);
    for(int i = 0 ; i < 6 ; i++){
        cin >> sum[i];
    }
    double a = sqrt((static_cast<double>(sum[0]) - sum[4]) * (static_cast<double>(sum[0]) - sum[4]) +
                    (static_cast<double>(sum[1]) - sum[5]) * (static_cast<double>(sum[1]) - sum[5]));
    double ab = a1(sum[0], sum[1], sum[2], sum[3]);
    double bc = a1(sum[2], sum[3], sum[4], sum[5]);
    double ac = a1(sum[0], sum[1], sum[4], sum[5]);
    double sum1 = ab + bc + ac;
    cout << fixed << setprecision(2) << sum1;
    return 0;
 }
