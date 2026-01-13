#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> vec = {3, 1, 4, 2, 5};
    int min_index = 0;
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[min_index]) 
            min_index = i;
    }
    int a = 0 ; 
    for (int b : vec){
        a += b ;
    }
    double d = a / vec.size() ;
    cout << "最小值: " << vec[min_index] 
              << "，下标: " << min_index << " " << d << endl ;
    return 0;
}
