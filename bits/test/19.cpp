#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int count = 0 ,count1 = 0;
int prepare (string s,string a){
    istringstream ss(s);
    istringstream aa(a);
    string s_ ;
    string a_ ;
    while(getline(ss,s_) && getline(aa,a_)){
        for (size_t i = 0; i < s_.size() && i < a_.size(); ++i) {
            if (s_[i] == a_[i]) count++;
        }
    }
    return count;
}
int counter(string s){  
    for(char c: s) count1++;
    return count1;
}
int main (){
    string s , a;
    string line;
    while (getline(cin, line) && line != "EOF") {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // 去掉 CR
        if (!s.empty()) s.push_back('\n');
        s += line;
    }
    while (getline(cin, line) && line != "EOF") {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // 去掉 CR
        if (!a.empty()) a.push_back('\n');
        a += line;
    }
    string t;
    t.reserve(a.size());
    for (char ch : a) {
        if (ch == '<') {
                if (!t.empty() && t.back() != '\n') t.pop_back();
        } else {
                t.push_back(ch);
        }
    }
    a = t;
    string ts;
    ts.reserve(s.size());
        for (char ch : s) {
            if (ch == '<') {
                if (!ts.empty() && ts.back() != '\n') ts.pop_back();
            } else {
                ts.push_back(ch);
            }
        }
        s = ts;
    int n ;
    cin >> n;
    int fin = prepare(s, a);
    int finial = (n > 0) ? int(fin * 60.0 / n + 0.5) : 0;
    cout << finial ;
    return 0;
}