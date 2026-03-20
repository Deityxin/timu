#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    int N , M;
    cin >> N >> M;
    vector<int> shu;
    for(int i = N; i <= M; i++){
        shu.push_back(i);
    }
    int ans0 = 0 , ans1 = 0 , ans2 = 0 , ans3 = 0 , ans4 = 0;
    int ans5 = 0 , ans6 = 0 , ans7 = 0 , ans8 = 0 , ans9 = 0;
    for(int a: shu){
        string s = to_string(a);
        for(auto s1: s){
            if(s1 == '0') ans0++;
            if(s1 == '1') ans1++;
            if(s1 == '2') ans2++;
            if(s1 == '3') ans3++;
            if(s1 == '4') ans4++;
            if(s1 == '5') ans5++;
            if(s1 == '6') ans6++;
            if(s1 == '7') ans7++;
            if(s1 == '8') ans8++;
            if(s1 == '9') ans9++;
        }
    }
    cout << ans0 << " " << ans1 << " " << ans2 << " " << ans3 << " " << ans4 << " "
         << ans5 << " " << ans6 << " " << ans7 << " " << ans8 << " " << ans9;
    return 0;
}