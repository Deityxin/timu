#include <iostream> 
#include <vector>
using namespace std;
int main () {
    vector<int> int_data;
    for (int j = 0; j < 10; j++){
        int num ;
        cin >> num ;
        int_data.push_back(num);
    }
    const int* begin = int_data.data();
    const int* end = int_data.size() + begin ;
    for (const int* p = end - 1 ; p >= begin ; p--){
        cout << *p << endl;
    }
    return 0 ;  
}