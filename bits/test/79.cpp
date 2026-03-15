#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std ;
int main (){
    int a , b ;
    cin >> a >> b ;
    vector<int> shu ;

    for(int i = 1 ; i <= b ; i++){
        if(i == 1) { continue ;}
        else if (i == 2) { 
            shu.push_back(i) ;
        }
        else if (i % 2 == 0) {
            continue ;
        }
        else{
            bool isPrime = true;
            int n = sqrt(i);
            for (int j = 3; j <= n; j += 2) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                shu.push_back(i);
            }
        }
    }

    vector<int> shu1;
    for (int s : shu) {
        if (s >= a && s <= b) {
            shu1.push_back(s);
        }
    }

    vector<int> ans;
    for (int lin : shu1) {
        string st = to_string(lin);
        bool ok = true;
        for (int i = 0; i < (int)st.size() / 2; i++) {
            if (st[i] != st[st.size() - 1 - i]) {
                ok = false;
                break;
            }
        }
        if (ok) ans.push_back(lin);
    }

    for (int x : ans) {
        cout << x << '\n';
    }
    return 0 ;
}