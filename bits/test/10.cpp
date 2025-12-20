#include <iostream>
#include <vector>
using namespace std;
int main (){
    int l , m ,count = 0;
    cin >> l >> m;
    vector <int> area , start_data(l+1,1);
    for (int i = 0; i < 2*m ; i++){
        int prepare ;
        cin >> prepare ;
        area.push_back(prepare) ;
    }
    for (int j = 0 ;j < area.size() ; j+=2){
        int a = area[j], b = area[j + 1] ;
        for(a ; a <= b ;a++){
            if(start_data[a] == 0) continue;
            else{
                start_data[a] = 0 ;
            }
        }
    }
    for (int k = 0; k < start_data.size();k++){
        if(start_data[k] == 1) count++;
    }
    cout << count ;
    return 0;
}