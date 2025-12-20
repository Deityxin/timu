#include <iostream>
#include <vector>
using namespace std;
int main (){
    int n , count = 0;
    cin >> n;
    vector <int> num;
    for (int i = 0;i < n; i++){
        int c ;
        cin >> c ;
        num.push_back(c) ;
    }
    for (int j = 0 ;j < n; j++){
        bool symbol = false;
        for(int k = 0; k < n && !symbol; k++){
            for (int l = k + 1; l < n; l++){
                if(num[j] == num[k] + num[l]){
                    count++ ;
                    symbol = true;
                    break ;
                }
             }
        }
    }
    cout << count ;
    return 0;
}