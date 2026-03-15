#include <iostream>
#include <vector>
#include <cmath>
using namespace std ;
int main (){
    int L ;
    cin >> L ;
    int sum = 0 ;
    vector<int> shu ;

    for(int i = 1 ; i <= L ; i++){
        if(i == 1) { continue ;}
        else if (i == 2) { 
            sum += i ;
            shu.push_back(i) ;
        }
        else if (i % 2 == 0) {
            continue ;
        }
        else{
            bool isPrime = true;
            int n = sqrt(i);
            for (int j = 3; j <= n; j += 2) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                if (sum + i > L) break;
                sum += i;
                shu.push_back(i);
            }
        }
    }
    for(int s : shu){
        cout << s <<'\n' ;
    }
    cout << shu.size() << '\n' ;
    return 0 ;
}