#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> add(vector<int> &a,vector<int> &b){
    if(a.size() < b.size()) return (b , a);
    int t = 0;
    vector<int> c;
    for(int i = 0; i < a.size() ; i++){
        t += a[i];
        if(i < b.size()) t = t + b[i];
        c.push_back(t % 100);
        t /= 100;
    }
    if(t) c.push_back(t);
    return c;
}
int main(){
    int n;
    cin >> n;
    vector<int> tem(n + 1 , 0);
    for(int i = 2 ; i <= n ; i++){
        tem[i] = add(tem[i - 2] , tem[i - 1]);
    }
    if(n == 1) cout << 1;
    else if(n == 2) cout << 2;
    else cout << ;
    return 0;
}