#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<vector<int>> shu(n , vector<int>(n));
    for(int i = 0; i < n; i++){
        shu[i][0] = 1; 
        shu[i][i] = 1;
        for(int j = 1; j < i; j++){
            shu[i][j] = shu[i - 1][j - 1] + shu[i - 1][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            cout << shu[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}