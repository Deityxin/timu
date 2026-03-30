#include <string>
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;
int main(){
    string s;
    getline(cin , s);
    vector<int> tem(128 , 0);
    vector<string> key = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };
    for(int i = 0; i < key.size() ; ++i){
        for(int j = 0; j < key[i].size(); j++){
            tem[key[i][j]] = j + 1;
        }
    }
    tem[' '] = 1;
    int sum = 0;
    for(char a: s){
        a = tolower(a);
        sum += tem[a];
    }
    cout << sum;
    return 0;
}