#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> primeFactors(int n) {
    vector<int> factors;
    int divisor = 2;
    
    while (divisor * divisor <= n) {
        while (n % divisor == 0) {
            factors.push_back(divisor);
            n /= divisor;
        }
        divisor++;
    }
    if (n > 1) factors.push_back(n);
    
    return factors;
}

int main (){
    int a;
    cin >> a;
    vector<int> sum = primeFactors(a);
    sort(sum.begin() , sum.end()) ;
    cout << sum[sum.size() - 1] << endl;
    return 0;
}