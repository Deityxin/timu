#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n , k;
    cin >> n >> k;
    vector<int> shu(n);
    for(int i = 0 ; i < n; i++){
        cin >> shu[i];
    }
    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
    int l = 0, r = n - 1;
    while(l < r){
        int pivot = shu[uniform_int_distribution<int>(l, r)(rng)];
        int i = l - 1, j = r + 1;
        while(i < j){
            do i++; while(shu[i] < pivot);
            do j--; while(shu[j] > pivot);
            if(i < j) swap(shu[i], shu[j]);
        }
        if(k <= j) r = j;
        else l = j + 1;
    }

    cout << shu[k];
    return 0;
}