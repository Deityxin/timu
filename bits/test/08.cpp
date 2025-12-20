#include <iostream>
#include <string>
#include <vector>
using namespace std ;
int main(){
    int c ;
    vector <int> f ;
    cin >> c ;
      if (c == 0) { 
        cout << 0;
        return 0;
    }
    string s = to_string(c) ;
    int str_len = s.size() ;
    bool started = false;
    if(c > 0){
        for(int i =str_len - 1;i >= 0 ; i--){
            if (!started) {
                if(s[i] == '0') continue;
                started = true ;
        }
        f.push_back(s[i] - '0');
    }
            for (int i = 0; i < f.size() ;i++){
            cout << f[i] ;
        }
    }else{
         for(int i =str_len - 1;i >= 0 ; i--){
            if(s[i] == '-') break ;
            if (!started) {
                if(s[i] == '0') continue;
                started = true ;
        }
        f.push_back(s[i] - '0');
         }
         cout << '-' ;
        for (int i = 0; i < f.size() ;i++){
            cout << f[i] ;
        }
    }
    return 0;
}