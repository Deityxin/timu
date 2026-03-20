#include <iostream>
#include <vector>
using namespace std;
void magic(vector<vector<int>>& dig, const vector<vector<int>>& dig1, int m){
    for(int i = 0; i < m; i++){
        int x = dig1[i][0] - 1;
        int y = dig1[i][1] - 1;
        int r = dig1[i][2];
        int z = dig1[i][3];
        int k = 2 * r + 1;
        int sx = x - r;
        int sy = y - r;
        vector<vector<int>> tmp(k, vector<int>(k));
        for(int a = 0; a < k; a++){
            for(int b = 0; b < k; b++){
                tmp[a][b] = dig[sx + a][sy + b];
            }
        }
        for(int a = 0; a < k; a++){
            for(int b = 0; b < k; b++){
                if(z == 0){
                    dig[sx + a][sy + b] = tmp[k - 1 - b][a];
                }else{
                    dig[sx + a][sy + b] = tmp[b][k - 1 - a];
                }
            }
        }
    }
}
int main(){
    int n , m;
    cin >> n >> m;
    int s = 1;
    vector<vector<int>> dig(n , vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dig[i][j] = s;
            s = s + 1;
        }
    }
    vector<vector<int>> dig1(m , vector<int>(4));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 4; j++){
            cin >> dig1[i][j];
        }
    }
    magic(dig , dig1 , m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j) cout << ' ';
            cout << dig[i][j];
        }
        cout << '\n';
    }
}