#include <iostream>
#include <vector>
using namespace std;
int main(){
    int a , b , c;
    cin >> a >> b >> c;
    vector<int> fin(a + b + c + 1 , 0);
    for(int i = 1 ; i <= a ; i++){
        for(int j = 1 ; j <= b ; j++){
            for(int k = 1; k <= c ; k++){
                fin[i + j + k]++;
            }
        }
    }
    int ans = 3;
    int best = 0;
    for(int i = 3; i < a + b + c + 1 ; i++){
        if(fin[i] > ans){
            ans = fin[i];
            best = i;
        }
    }
    cout << best << endl;
    return 0;
}