#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    if (!(cin >> a >> b)) return 0;

    if (a == "0" || b == "0") {
        cout << 0;
        return 0;
    }

    vector<int> A, B;
    for (int i = (int)a.size() - 1; i >= 0; --i) A.push_back(a[i] - '0');
    for (int i = (int)b.size() - 1; i >= 0; --i) B.push_back(b[i] - '0');

    vector<int> C((int)A.size() + (int)B.size() + 1, 0);

    for (int i = 0; i < (int)A.size(); ++i) {
        for (int j = 0; j < (int)B.size(); ++j) {
            C[i + j] += A[i] * B[j];
        }
    }

    for (int k = 0; k + 1 < (int)C.size(); ++k) {
        C[k + 1] += C[k] / 10;
        C[k] %= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();

    for (int i = (int)C.size() - 1; i >= 0; --i) cout << C[i];
    return 0;
}