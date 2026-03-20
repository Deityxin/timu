#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n , m;
    cin >> n >> m;
    vector<int> shu;
    while(m > 0){
        int a;
        cin >> a;
        shu.push_back(a);
        m--;
    }
    sort(shu.begin() , shu.end());
    for(int a: shu) cout << a << ' ';
    return 0;
}