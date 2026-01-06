#include <iostream>
#include <vector>
using namespace std;
int lookfor(const vector<long long> &dig , int a ,vector<long long> &mem){
    for(long long j = 0; j < dig.size() ; j++){
        long long c = dig[j] % a ;
        mem[j] = c ;
    }
    for(long long k = 1 ; k < mem.size() - 1 ; k++){
        if(mem[k] == 0 && mem[k + 1] == 1) return k;
    }
    return -1;
}

int main (){
    long long a ;
    cin >> a;
    int e = (a + 1) * (a + 1);
    vector<long long> dig(e , 0);
    vector<long long> mem(e);
    dig[0] = 0 ; dig[1] = 1;
    for(long long i = 2 ; i < e ; i++ ){
        dig[i] = dig[i - 1] + dig[i - 2];
    }
    int test = lookfor(dig , a , mem);
    cout << test << endl;
    return 0;
}// 优化 边计算边取模  否则会造成空间的溢出