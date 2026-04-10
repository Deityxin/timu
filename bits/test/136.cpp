#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    int ans = 1;
    for(int i = 0; i < n - 1 ; i++){
        ans = 2*(ans) + 2;
    }
    cout << ans;
    return 0;
}