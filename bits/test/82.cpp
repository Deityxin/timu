#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main (){
    int n;
    cin >> n;
    vector<int> temp(n);
    for(int i = 0 ; i < temp.size() ; i++){
        cin >> temp[i];
    }
    sort(temp.begin() , temp.end());
    cout << temp[temp.size() - 1] - temp[0];
    return 0;
}