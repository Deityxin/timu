#include <iostream>
using namespace std;
int minium(int a, int b){
    if (a > b){
        return b;
    }else{
        return a;
    }
}
int price(int a, int b, int c){
    if( a % b != 0){
         int price = ((a / b)+1) * c;
        return price;
    }else{
        int price = (a / b) * c;
        return price;
    }
}
int main (){
    int a;//所需要购买的铅笔数量
    cin >> a;
    int b , c;// b表示铅笔数量 c表示包装价格
    int e , f;
    int g , h;
    cin >> b >> c >> e >> f >> g >> h; 
    int price1 = price(a , b , c);
    int price2 = price(a , e , f);
    int price3 = price(a , g , h);
    int minprice = minium (price1 , minium(price2,price3));
    cout << minprice << endl;
    return 0;
}