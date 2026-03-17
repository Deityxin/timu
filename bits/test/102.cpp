#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
int main(){
     int a;
     cin >> a;
     vector<int> fin;
     vector<vector<int>> sum(a,vector<int>(3));
     vector<string> lin;
     for(auto &s: sum){
          string s1;
          int summary = 0;
          cin >> s1 >> s[0] >> s[1] >> s[2];
          summary = s[0] + s[1] + s[2];
          lin.push_back(s1);
          fin.push_back(summary);
     }
     for(int i = 0; i < a; i++){
          for(int j = i + 1;j < a; j++){
               if(abs(sum[i][0] - sum[j][0]) <= 5 && abs(sum[i][1] - sum[j][1])  <= 5 && abs(sum[i][2] - sum[j][2])  <= 5 &&  abs(fin[i] - fin[j]) <= 10){
                    cout << lin[i] << ' '  << lin[j] << '\n';
               }
          }
     }
     return 0;
}