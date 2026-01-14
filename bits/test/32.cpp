#include <iostream>
#include <string>
#include <vector>
using namespace std;
int fin = 0 ;
void simulate (const string& s , int a){
    for(char s_ : s){
        if(s_ == '2') fin++ ;
    }
    return ;
}
int main (){
    int a , b ;
    cin >> a >> b ;
    vector<int> dig ;
    for (int i = a ; i <= b ; i++ ){
        dig.push_back(i) ;
    }
    for (int dig1 : dig){
        simulate(to_string(dig1) , fin) ;
    }
    cout <<  fin << endl  ;
    return 0 ;
}