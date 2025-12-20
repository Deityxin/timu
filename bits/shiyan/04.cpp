#include <iostream> 
using namespace std;
int main (){
    int count = 0 ;
    for (int x = 0;x >= 0 && x <= 10; x++){
        for(int y = 0;y >= 0 && y <=20;y++){
            for (int z = 0;z >= 0 && z <= 100; z++){
                10*x + 5*y + z ==100;
                count ++;
            }
        }
    }
    cout << count <<endl ;
    return 0;
}