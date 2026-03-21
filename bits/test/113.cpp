 #include <iostream>
 #include <vector>
 #include <algorithm>
 using namespace std;
 int main(){
    int a;
    cin >> a;
    vector<vector<double>> cns(a , vector<double>(2));
    for(auto &s: cns){
        double b;
        int b1;
        cin >> b >> b1;
        s[0] = b;
        s[1] = b1;
    }
    int best = 0;
    for(auto s1: cns){
        int c = static_cast<int>((s1[0] + 1) * s1[1]);
        if(c > best) best = c;
    }
    vector<int> tem(best + 1 , 0);
    for(auto s2: cns){
        for(int i = 1 ; i <= s2[1] ; i++){
            if(tem[i * s2[0]] == 0) tem[i * s2[0]] = 1;
            else tem[i * s2[0]] = 0;
        }
    }
    auto it = find(tem.begin() , tem.end() , 1);
    if (it != tem.end()) {
        cout <<  it - tem.begin();           
    }
    return 0;
 }