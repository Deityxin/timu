#include <iostream>
#include <iomanip>
using namespace std;
int main (){
    int s , v , a  ;
    cin >> s >> v ;
    if(s % v == 0){
        a = s / v ;
    }else{
        a = (s / v) + 1 ;
    }
    int b = a + 10 ; 
    int t = (480 - b) % (24 * 60);
    if(t < 0) t += 24 * 60;
    int h = t / 60;
    int m = t % 60;
    cout << setfill('0') << setw(2) << h << ":" << setw(2) << m ;
    return 0 ;
}