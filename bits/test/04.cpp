#include <iostream>
#include <vector>
using namespace std;
int saved_money = 0 ;
int have_money = 0 ;
double price_total (double last){
    double total = saved_money * 1.2 + have_money ; 
    return total; 
}
void price_last (int a , int i){
    have_money += 300;
    have_money -= a ;
    if (have_money < 0){
        cout << "-" << i + 1 << endl;
        exit(0);
    }else{
        int k = have_money / 100 ;
        saved_money += k * 100 ;
        have_money -= k * 100 ;
    }
}
int main (){
    vector <int> data; // 用数组来优化输出和输入
    for (int i = 0; i < 12; i++){
        int num ;
        cin >> num ;
        data.push_back(num);
    }
    size_t len = data.size();
    for (int i = 0; i < len ; i++){
        price_last (data [i] , i);
    }
    int total = price_total (saved_money);
    cout << total << endl;
    return 0;
}
// 全局变量的使用 以及一些小的细节  调试用的代码要记得删掉因为oc的时候会出问题
// 还有就是vector的使用  以及size_t的使用 
// 以及exit(0)的使用  这些都是平时不太注意的点  还有逻辑上的错误