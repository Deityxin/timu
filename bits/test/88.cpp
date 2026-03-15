#include <iostream>
#include <vector>
using namespace std;
bool isLeapYear(int year) {
    if(year <= 0 || year > 9999) return false;
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int main (){
    int a , b;
    cin >> a >> b;
    vector<int> shu;
    vector<int> fin;
    for(int i = a; i <= b ;i++) shu.push_back(i);
    for(int s: shu){
        if(isLeapYear(s)){
            fin.push_back(s);
        }
    }
    cout << fin.size() << '\n' ;
    for(int s1:fin) cout << s1 << ' ';
    return 0;
}