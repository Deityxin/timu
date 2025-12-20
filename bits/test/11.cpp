#include <iostream>
#include <vector>
using namespace std ;
int main () {
    vector<long long > num;
    long long i ;
    do{
        cin >> i;
        num.push_back(i);
    }while(i != 0);
    if (num.size() == 1)  return 0;
    else
    for (int j =  num.size() - 2; j >= 0 ;j--){
        if(j == num.size() - 2) cout << num[j] ;
        else cout << " " << num[j] ;
    }
    return 0 ;
}