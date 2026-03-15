#include <iostream>
#include <string>
using namespace std;
int main(){
    int a;
    cin >> a;
    string name, best_name;
    int c, m, e;
    int best_c = 0, best_m = 0, best_e = 0;
    int best_sum = -1;
    for (int i = 0; i < a; i++) {
        cin >> name >> c >> m >> e;
        int sum = c + m + e;
        if (sum > best_sum) {
            best_sum = sum;
            best_name = name;
            best_c = c;
            best_m = m;
            best_e = e;
        }
    }
    cout << best_name << " " << best_c << " " << best_m << " " << best_e;
    return 0;
}