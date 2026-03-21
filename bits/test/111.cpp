#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n , m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> fin;
    for(int i = 0; i < n; i++) cin >> a[i];
    if(n == m){
        int ans1 = 0;
        for(int s: a){ ans1 += s ;}
        cout << ans1 ;
    }else{
        for(int j = 0; j < n - m; j++){
            int ans = 0;
            for(int k = j; k < j + m;k++){
                ans += a[k];
            }
        fin.push_back(ans);
        }
    sort(fin.begin() , fin.end());
    cout << fin[0] << endl;
    }
    return 0;   
}