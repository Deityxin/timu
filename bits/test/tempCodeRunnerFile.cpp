#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std ;
int main (){
    int n ;
    cin >> n ;
    vector<string> a(n);
    sort(a.begin(), a.end(), [](const string& x, const string& y) {
        return x + y > y + x;
    });
    if (all_of(a.begin(), a.end(), [](const string& s) { return s == "0"; })) {
        cout << 0;
        return 0;
    }
    for (auto& s : a) cout << s;
    return 0;
}