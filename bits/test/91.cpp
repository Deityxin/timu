#include <iostream>
#include <vector>
using namespace std;

void fix(vector<vector<int>>& a, int x, int y, int size) {
    if (size == 1) return;
    int half = size / 2;
    for (int i = x; i < x + half; i++) {
        for (int j = y; j < y + half; j++) {
            a[i][j] = 0;
        }
    }
    fix(a, x, y + half, half);
    fix(a, x + half, y, half);
    fix(a, x + half, y + half, half);
}

int main() {
    int n;
    cin >> n;
  
    int a = 1;
    for (int i = 0; i < n; i++) {
        a *= 2;
    } 

    vector<vector<int>> shu(a, vector<int>(a, 1));

    fix(shu, 0, 0, a);

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            cout << shu[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}