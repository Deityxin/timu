#include <iostream>
#include <algorithm>
#include <vector>
using namespace std ;
int main (){
    vector<int> a ;
    for(int i = 0 ; i < 3 ; i++){
        int b ;
        cin >> b ;
        a.push_back(b) ;
    }
    sort(a.begin() , a.end()) ;
    if(a[0] + a[1] <= a[2]) cout << "Not triangle" << "\n" ;
    else if (a[0] * a[0] + a[1] * a[1] == a[2] * a[2]) cout << "Right triangle" << '\n' ;
    else if (a[0] * a[0] + a[1] * a[1] > a[2] * a[2]) cout << "Acute triangle" << '\n' ;
    else if (a[0] * a[0] + a[1] * a[1] < a[2] * a[2]){
        cout << "Obtuse triangle" << '\n' ;
    }
    if (a[0] + a[1] > a[2] && a[0] == a[1]) cout << "Isosceles triangle" << '\n' ;
    if(a[0] == a[1] && a[1] == a[2]) cout << "Equilateral triangle" << endl ;
    return 0 ;
}