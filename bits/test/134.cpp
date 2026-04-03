#include <iostream>
#include <string>
#include <vector>
using namespace std;
char lin[] = {
    'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' ,
    'J' , 'K' , 'L' , 'M' , 'N' , 'O' , 'P' , 'Q' , 'R' ,
    'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' , 'Z'
};
vector<vector<char>> tem(26);
void xun(string s){
    for(char a : s){
        if(a >= 'A' && a <= 'Z'){
            tem[a - 'A'].push_back('*');
        }
    }
}
string fo(string s){
    return s;
}
int main(){
    string s1 , s2 , s3 , s4;
    getline(cin , s1);
    getline(cin , s2);
    getline(cin , s3);
    getline(cin , s4);
    xun(fo(s1)); xun(fo(s2));
    xun(fo(s3)); xun(fo(s4));
    int mx = 0;
    for(int i = 0; i < 26; i++){
        if((int)tem[i].size() > mx) mx = (int)tem[i].size();
    }
    for(int i = mx; i >= 1; i--){
        for(int j = 0; j < 26; j++){
            if((int)tem[j].size() >= i) cout << '*';
            else cout << ' ';
            if(j != 25) cout << ' ';
        }
        cout << '\n';
    }
    for(int i = 0; i < 26; i++){
        cout << lin[i];
        if(i != 25) cout << ' ';
    }
    return 0;
}