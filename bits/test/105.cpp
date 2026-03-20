#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; 
    cin >> t;
    while(t--){
        int a , b;
        cin >> a >> b;
        vector<int> f(1,1);
        for(int i = 2; i <= a; i++ ){
            int carry = 0;
            for(int &s : f){
                int x = s * i + carry;
                s = x % 10;
                carry = x / 10;
            }
            while(carry){
                f.push_back(carry % 10);
                carry /= 10;
            }
        }
        int ans = 0;
        for(int c:f) if(c == b) ans++;
        cout << ans << '\n';
    }
    return 0;
}