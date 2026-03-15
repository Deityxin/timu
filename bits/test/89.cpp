#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int main(){
    int a , b;
    cin >> a >> b;
    vector<vector<int>> shu(a,vector<int>(b));
    vector<int> fin;
    for(int i = 0 ; i < a ; i++){
        for(int j = 0 ; j < b; j++){
            cin >> shu[i][j];
        }
    }
    for(auto& row:shu){
        sort(row.begin() , row.end());
    }
    for(auto& mm:shu){
        int sum = 0;
        for(int i = 1 ; i < mm.size() - 1; i++){
            sum += mm[i];
        }
        fin.push_back(sum);
    }
    sort(fin.begin() , fin.end());
    cout << fixed << setprecision(2) << static_cast<double>(fin[fin.size() - 1]) / (b - 2);
    return 0;
}