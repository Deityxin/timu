#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int n;
bool panduan(vector<string> s, vector<string> a) {
    for (int i = 0; i < n; i++) {
        if (s[i] != a[i]) return false;
    }
    return true;
}
vector<string> zhuan(vector<string> s) {
    vector<string> tem = s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            tem[i][j] = s[n - 1 - j][i];
        }
    }
    return tem;
}
vector<string> fan(vector<string> s) {
    vector<string> tem = s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            tem[i][j] = s[i][n - 1 - j];
        }
    }
    return tem;
}
int main (){
    cin >> n;
    vector<string> s(n), a(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<string> tem = zhuan(s);
    if(panduan(tem, a)) { cout << 1 << endl; return 0; }
    tem = zhuan(tem);
    if(panduan(tem, a)) { cout << 2 << endl; return 0; }
    tem = zhuan(tem);
    if(panduan(tem, a)) { cout << 3 << endl; return 0; }
    tem = fan(s);
    if(panduan(tem, a)) { cout << 4 << endl; return 0; }
    for(int i = 0; i < 3; i++) {
        tem = zhuan(tem);
        if(panduan(tem, a)) { cout << 5 << endl; return 0; }
    }
    if(panduan(s, a)) { cout << 6 << endl; return 0; }
    cout << 7 << endl;
    return 0;
}