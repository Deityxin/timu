#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> dig;
    dig.push_back(n);
    while(n != 1){
        if(n % 2 == 0){
            n = n / 2;
            dig.push_back(n);
        }else{
            n = (n * 3) + 1;
            dig.push_back(n);
        }
    }
    for(int m = dig.size() - 1; m >= 0 ; m--){
        cout << dig[m] << ' ';
    }
    return 0;
} 