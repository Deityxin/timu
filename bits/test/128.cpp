#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    string s;
    cin >> n >> s;
    if(n <= 1){
        cout << 0;
        return 0;
    }
    int ans = 0;
    int tem = 0;
    for(int i = 0; i < s.size() - 1 ; i++){
        if(s[i] == 'V' && s[i + 1] == 'K') ans += 1;
        else if(s[i] == 'V' && s[i + 1] == 'V' && s[i + 2] != 'K') tem = 1;
        else if(s[i] == 'K' && s[i + 1] == 'K' && s[i - 1] != 'V') tem = 1;
    }
    if(tem == 1) ans += 1;
    cout << ans;
    return 0;
}