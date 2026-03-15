#include <iostream>
#include <vector>
using namespace std ;
int main (){
    int n ;
    cin >> n ;
    vector<int> sum ;
    int temp = 0 ;
    int qian = 1 ;
    int cnt = 0 ;
    while(temp != n){
        temp += 1 ;
        sum.push_back(qian) ;
        cnt += 1 ;
        if(cnt == qian){
            qian += 1 ;
            cnt = 0 ;
        }
    }

    int ans = 0 ;
    for(int x : sum) ans += x ;
    cout << ans ;
}