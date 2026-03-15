#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
int main(){
    int a;
    cin >> a;
    vector<int> shu(a);
    for(int i = 0; i < a; i++) cin >> shu[i];
    sort(shu.begin() , shu.end());
    int sum = 0;
    for(int j = 1; j < a - 1; j++){
        sum += shu[j];
    }
    cout << fixed << setprecision(2) << static_cast<double>(sum) / (a - 2) << endl;
    return 0;
}