 #include <iostream>
 #include <vector>
 using namespace std;
 int fin (int N , int K ,vector<int>&  mem){
    if (mem[N] != -1)  return mem[N];
    if (N == 0) return 1;
    if (N < 0) return 0;
    else{
        int fin1 = 0;
        for (int i = 1; i <= K; i++){
            if(N - i == 0) fin1 += 1;
            else if((N - i) > 0) fin1 += fin(N - i,K ,mem);
        }
        mem[N] = fin1 ;
        return fin1;
    }
 }
 int main (){
    int N , K;
    cin >> N >> K;
    vector<int> mem(N + 1, -1);
    int result = fin(N , K ,mem);
    cout << result % 100003;
    return 0;
 }