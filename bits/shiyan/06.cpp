#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int max_(const vector<vector<int>>& sta,vector<int> fin){
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 4; j++){
            fin.push_back(sta[i][j]);
        }
    }
    sort(fin.begin(),fin.end());
    int c = fin[fin.size() - 1];
    for(int i = 0; i < 3; i++){
        auto it = find(sta[i].begin(),sta[i].end(),c);
        if(it != sta[i].end()){
            auto fin_1 = it - sta[i].begin();
            cout << i+1 <<' '<< fin_1 + 1 <<' ';
            break;
        }
    }
    return c;
}
int main (){
    vector<vector<int>> sta(3,vector<int>(4));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            int x ;
            cin >> x ;
            sta[i][j] = x;
        }
    }
    vector<int> fin;
    int c = max_(sta,fin);
    cout << c;
    return 0;
}