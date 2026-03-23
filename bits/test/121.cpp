#include <iostream>
#include <string> 
#include <algorithm>
#include <vector>
using namespace std;
bool isPrime(int x){
    if(x < 2) return false;
    if(x == 2 || x == 3) return true;
    if(x % 2 == 0 || x % 3 == 0) return false;
    for(int i = 5 ; 1ll * i * i  <= x ; i += 6){
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}
int main(){
    string s;
    getline(cin , s);
    int ans = 1;
    vector<int> shu;
    sort(s.begin() , s.end());
    for(int i = 0; i < s.size() - 1; i++){
         if(s[i] == s[i+1]){ 
             ans++; 
         }
         else{
             shu.push_back(ans);
             ans = 1;
         }
    }
    shu.push_back(ans);
    sort(shu.begin() , shu.end());
    if(isPrime(abs(shu[0] - shu[shu.size() - 1]))) cout << "Lucky Word" << '\n' << abs(shu[0] - shu[shu.size() - 1]);
    else cout << "No Answer" << "\n" << 0;
    return 0;
}