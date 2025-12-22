#include <iostream>
#include <string>
using namespace std;
int main (){
    string s;
    getline(cin,s);
    for (int i = 0;i < s.size(); i++){
        if(s[i] == ' '){
            for(int j = i;j < s.size() - i;j++){
                s[j] = s[j+1] ;
            }
            s.pop_back();
            --i;
        }
    }
    for (int i = 0;i < s.size();i++){
        cout << s[i];
    }
    return 0;
}