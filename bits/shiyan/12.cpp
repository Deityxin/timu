#include <iostream>
#include <string>
using namespace std;
class Controller{
    double KP , K1 , KD;
public:
    string panduan (){
        if(KP == 0) return "Error";
        if(KP != 0 && K1 == 0 && KD == 0) return "P";
        if(KP != 0 && K1 != 0 && KD == 0) return "PI";
        else return "PID";
    }
    Controller (double a = 0 ,double c = 0 , double d = 0) : KP(a) , K1(c) , KD(d){}
};
int main (){
    Controller object1(1.2 , 2 , 3);
    Controller object2(1.2 , 0 , 2);
    Controller object3(1.2 , 0 , 0);
    string s = object1.panduan();
    for(char a: s){
        cout << a;
    }
    return 0;
}