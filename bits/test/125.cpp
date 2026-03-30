#include <iostream>
using namespace std;
int main(){
    long long n , m;
    cin >> n >> m;
    long long rect = n * (n + 1) * m * (m + 1) / 4;
    long long s = n < m ? n : m;
    long long sq = 0;
    for (long long k = 1; k <= min(n, m); k++) {
        sq += (n - k + 1) * (m - k + 1);
    }
    cout << sq << ' ' << rect - sq;
    return 0;
}