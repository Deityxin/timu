#include <iostream>
#include <vector>
using namespace std;
int main (){
    vector<vector<int>> dig(5,vector<int>(5,0));
    int a = 0;
    for(int i = 0;i < 5;i++){
        int* row = dig[i].data();         
        for(int j = 0;j < 5;j++){
            a += 1;
            *(row + j) += a;             
        }
    }
    for (int i = 0; i < 5; ++i) {
        const int* row = dig[i].data();     
        for (int j = 0; j < 5; ++j) {
            if (j) cout << ' ';
            cout << *(row + j);              
        }
        cout << '\n';
    }
    for (int i = 0; i < 5; i++){
        int *di = dig[i].data();
        for (int j = i+1;j < 5;j++){
            *(di + j) = 0;
        }
    }
    for (int i = 0; i < 5; ++i) {
        const int* row = dig[i].data();     
        for (int j = 0; j < 5; ++j) {
            if (j) cout << ' ';
            cout << *(row + j);              
        }
        cout << '\n';
    }
    return 0;
}
