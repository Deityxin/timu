#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
string lin[] = {
    "zero", "one", "two", "three", "four", "five", 
    "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen", "twenty"
};
int find1(string s[] , string a){
    for(int i = 0 ; i < 21 ; i++){
        if(s[i] == a) return i;
    }
    return -1;
}
string zhuan(int a){
    a = a * a;
    a = a % 100;
    if(a < 10) return "0" + to_string(a);
    return to_string(a);
}
int main(){
    string line;
    getline(cin , line);
    stringstream ss(line);
    string one;
    vector<string> tem;
    while(ss >> one) tem.push_back(one);
    vector<string> fin;
    for(auto a: tem){
        if(find1(lin , a) != -1){
            fin.push_back(zhuan(find1(lin , a)));
        }else if(a == "a"){
            fin.push_back(zhuan(1));
        }else if(a == "both") fin.push_back(zhuan(2));
        else if( a == "another") fin.push_back(zhuan(1));
        else if(a == "first") fin.push_back(zhuan(1));
        else if(a == "second") fin.push_back(zhuan(2));
        else if(a == "third") fin.push_back(zhuan(3));
    }
    sort(fin.begin(), fin.end(), [](const string& x, const string& y) {
        return x + y < y + x;
    });
    string ans;
    for (auto& s : fin) ans += s;
    if(ans.size() == 0) cout << 0;
    int p = 0;
    while(p + 1 < ans.size() && ans[p] == '0') p++;
    cout << ans.substr(p);
    return 0;
}