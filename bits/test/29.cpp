#include <iostream>
#include <vector>
using namespace std;
int fin (int a , int b){
    if (a == 0 && ( b == 2 ||  b == 3)) return 1;
    else if ( a == 1 && ( b == 0 ||  b == 3)) return 1;
    else if ( a == 2 && ( b == 1 ||  b == 4)) return 1;
    else if ( a == 3 &&  (b == 2 ||  b == 4)) return 1;
    else if ( a == 4 && ( b == 0 ||  b == 1)) return 1;
    else return 0;
}
int main () {
    int N , Na , Nb ;
    int c = 0 , d = 0;
    cin >> N >> Na >> Nb ;
    vector<int> dig(Na) ;
    vector<int> dig1(Nb) ;
    vector<vector<int>> fin1(2 , vector<int>(N , 0)) ;
    for (int i = 0 ; i < Na ; i++){
        cin >> dig[i] ;
    }
    for (int i = 0 ; i < Nb ; i++){
        cin >> dig1[i] ;
    }
    for (int j = 0 ; j < N ; j++){
        fin1[0][j] = dig[j % dig.size()];
        fin1[1][j] = dig1[j % dig1.size()];
    }
    for (int j = 0 ; j < N ; j++){
        c += fin(fin1[0][j] , fin1[1][j]);
        d += fin(fin1[1][j] , fin1[0][j]);
    }
    cout << c << " " << d << endl ;
    return 0 ; 
}