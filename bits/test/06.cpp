#include <iostream>
#include <vector>
using namespace std;
vector<double> se_data;
void sequence (int n){
    for (int i = 1; i < n + 1 ; i++){
        double a = 1.0 / i ;
        se_data.push_back (a);
    }
}
int compare (const vector<double> &se_data , int a){
    double sum = 0;
     for (int i = 0 ; i < se_data.size() ; i ++){
        sum += se_data [i];
        if(sum > a){
            return i + 1;
        }
    }
    return -1;
}
int main (){
    int a ;
    int n = 2000000;
    cin >> a ;
    sequence (n);
    cout << compare (se_data , a) << endl;
    return 0;
}