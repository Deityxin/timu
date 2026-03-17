#include <iostream>
#include <vector>
using namespace std;
int main(){
    int a;
    cin >> a;
    vector<int> shu;
    for(int i = 4; i <= a; i++){
        if(i % 2 == 0) shu.push_back(i);
    }
    
}