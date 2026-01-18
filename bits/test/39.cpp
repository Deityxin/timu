#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
using namespace std ;
static inline int money_of_row(const vector<string>& r){
    if (r.size() < 6) return 0;
    int sum = 0 ;
    int avg = stoi(r[1]) ;      
    int eva = stoi(r[2]) ;       
    char cadre = r[3][0] ;       
    char west  = r[4][0] ;      
    int paper = stoi(r[5]) ; 

    if (avg > 80 && paper > 0) sum += 8000 ;        
    if (avg > 85 && eva > 80)  sum += 4000 ;       
    if (avg > 90)              sum += 2000 ;       
    if (avg > 85 && west=='Y') sum += 1000 ;       
    if (eva > 80 && cadre=='Y')sum += 850 ;       
    return sum ;
}

static void solve(const vector<vector<string>>& s_, int N){
    int bestIdx = 0, bestMoney = money_of_row(s_[0]) ;
    long long total = bestMoney ;
    for(int i = 1; i < N; ++i){
        int cur = money_of_row(s_[i]) ;
        total += cur ;
        if (cur > bestMoney){ bestMoney = cur ; bestIdx = i ; }
    }
    cout << s_[bestIdx][0] << "\n" << bestMoney << "\n" << total << "\n" ;
}
int main (){
    int N ;
    cin >> N ;
     cin.ignore(numeric_limits<streamsize>::max(), '\n') ;
    vector<vector<string>> s_(N) ;
    for(int i = 0 ; i < N ; i++){
        string line ;
        getline(cin , line) ;
        stringstream ss(line) ;
        string line1 ;
        vector<string> lin ;
        while(ss >> line1) lin.push_back(line1) ;
        s_[i] = move(lin) ;
    }
    solve(s_, N);
    return 0 ;
}