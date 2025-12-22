#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> dig;
    for(int x ; cin >> x;) dig.push_back(x);
    if(dig.size() % 2 == 0){
        for(int i = 0;i < dig.size();i+=2){
            int a = dig[i] + dig[i+1];
            cout << " "<< a;
        }
    }else{
        cout << dig[dig.size() - 1];
        int b = dig.size() / 2;
        for(int j = 0; j < b;j++){
            int c = dig[j] + dig[dig.size() - j -1];
            cout <<" "<< c;
        }
    }
    return 0;
}