#include <iostream>
#include <string>
#include <vector>
using namespace std ;
int main () {
    int N ; 
    cin >> N ;
    vector<vector<int>> dig(N , vector<int>(N)) ;
    dig[0][(N / 2) + 1] = 1 ;
    for(int i = 2 ; i <= N * N ; i++){
        if((i - 1 == 0) && i )
    }
}