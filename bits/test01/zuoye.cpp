#include <iostream>
using namespace std;
template<class T>
T compare(T a , T b ,bool c){
    if(c == true){
        return a < b ? a : b; 
    }else return a < b ? b : a;
}
int main(){
    int a , b;
    cout << compare(a, b, true) << '\n';
    cout << compare(a, b, false) << endl;
}