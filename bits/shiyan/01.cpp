#include <iostream>
using namespace std;
int main () {
    int digatal = 0 , space = 0 , others = 0 ;
    int num ;
    while ((num = cin.get()) != EOF){
        char a = static_cast<char>(num);
        if(a >= '0' &&a <= '9'){
            digatal++;
        }else if(a ==' '){
            space++;
        }else{
            others++;
        }
    }
    cout << digatal << " " <<space << " " <<others << " " <<endl;
    return 0 ;
}
// cin.get() 返回值是整数形