#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int M = N / 364;

    for (int X = 100; X >= 1; X--) {
        int diff = M - X;
        if (diff > 0 && diff % 3 == 0) {
            int K = diff / 3;
            cout << X << '\n' << K << '\n';
            break;
        }
    }

    return 0;
}