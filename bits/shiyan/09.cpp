#include <iostream>
using namespace std;
int index(int array[], int num) {
    if(num == 3) return array[num] = 16;
    else return array[num];
}
int main() {
    int array[] = {2, 4, 6, 8, 10};
    int c = index(array , 3);
    for (int i = 0; i < 5; i++)
        cout << index(array, i) << ' ';
    cout << endl;
    return 0;
}