 #include <iostream>
 using namespace std;
 int main (){
    int bench = 30;
    int apple [10] ={} ;
    for (int i = 0 ; i <10 ; i++){
        int num ;
        cin >> num ;
        apple [i] = num ;
    }
    int max , count = 0 ;
    cin >> max ;
    for (int j = 0 ; j <= 9; j++){
        if(apple[j] <= max){
            count += 1 ;
        }else if(apple[j] <= max + bench){
            count += 1 ;
        }else continue ;
    }
    cout << count ;
 }