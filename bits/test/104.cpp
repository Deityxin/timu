#include <iostream>
#include <vector>
using namespace std;
int main(){
    int a;
    cin >> a;
    int s = 1;
    vector<vector<int>> dig(a , vector<int>(a));
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            dig[i][j] = s;
            s = s + 1;
        }
    }
}