#include <iostream>
using namespace std;
int main () {
    int char_front ;
     while ((char_front = cin.get()) != EOF){
        if(char_front >= 65 && char_front <= 90){
            char a = static_cast<char>(char_front + 32);
            cout << a  << '\n'; 
        }else if(char_front >= 97 && char_front <= 122){
            char a = static_cast<char>(char_front - 32);
            cout << a  << '\n'; 
        }else{
            cout << static_cast<char>(char_front) << '\n';
    }
}
    return 0;
}