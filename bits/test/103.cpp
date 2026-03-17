#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    for (int x = 4; x <= n; x += 2) {
        for (int p : primes) {
            if (p > x) break;
            if (isPrime[x - p]) {
                cout << x << "=" << p << "+" << x - p << '\n';
                break;
            }
        }
    }
    return 0;
}