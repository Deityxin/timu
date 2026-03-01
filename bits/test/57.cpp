#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std ;
int main (){
    int a , b ;
    cin >> a >> b ;
    vector<string> s_ ;
    string line ;
    cin.ignore() ;
    while(static_cast<int>(s_.size()) < a && getline(cin , line)){
        if(line.empty()) continue ;
        s_.push_back(line) ;
    }
    vector<string> ans = s_;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for(int i = 0; i < a; ++i){
        for(int j = 0; j < b; ++j){
            if(s_[i][j] == '?'){
                int mines = 0;
                for(int k = 0; k < 8; ++k){
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if(ni >= 0 && ni < a && nj >= 0 && nj < b && s_[ni][nj] == '*'){
                        ++mines;
                    }
                }
                
                ans[i][j] = char('0' + mines);
            }
        }
    }
    for(int i = 0; i < a; ++i){
        cout << ans[i] << '\n';
    }
}