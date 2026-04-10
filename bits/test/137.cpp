#include <iostream>
#include <string>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        int year , ex;
        cin >> s >> year >> ex;
        cout << s << ' ' << year + 1 << ' ';
        ex = ex * 1.2;
        if(ex >= 600) cout << "600" << '\n';
        else cout << ex << '\n';
    }
    return 0;
}