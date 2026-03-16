#include <iostream>
using namespace std;
struct student{
    int x;
    int y;
    int a;
    int sum(){
        return y + a;
    }
};
bool check(student s){
    if(s.sum() > 140 && s.y * 7 + s.a * 3 >= 800) return true;
    return false;
}
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        student s;
        cin >> s.x >> s.y >> s.a;
        if(check(s)) cout << "Excellent" << '\n';
        else cout << "Not excellent" << '\n';
    }
    return 0;
}