#include <iostream>
#include <vector>
using namespace std;
int main(){
    int a;
    cin >> a;
    vector<int> sum(a);
    vector<int> lin;
    for(int i = 0; i < a ; i++) cin >> sum[i];
    for(int i = a - 1 ; i >= 0 ; i--){
        int c = 0;
        for(int j = 0 ; j < i ;j++){
            if(sum[j] < sum[i]){
                c += 1;
            }
        }
        lin.push_back(c);
    }
    for(int k = lin.size() - 1; k >= 0; k--) cout << lin[k] << ' ';
    return 0;
}