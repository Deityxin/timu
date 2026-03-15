#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main (){
    int n;
    cin >> n;
    vector<int> temp;
    vector<int> fin;

    for(int i = 0 ; i < n ; i++){
        int a;
        cin >> a;
        temp.push_back(a);
    }

    for(int i = 0 ; i < n - 1 ; i++){
        int sum = 0;
        for(int j = 1 ; j < temp.size() ; j++) {
            if(i + j > temp.size()) break;
            if(temp[i + j - 1] + 1 == temp[i + j]){
                sum += 1;
                fin.push_back(sum);
            }else break;
        }
    }
    sort(fin.begin() , fin.end());
    cout << fin[fin.size() - 1] + 1 << endl;
    return 0;
}