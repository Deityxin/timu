#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
   int n;
   cin >> n;
   vector<vector<int>> lin(n, vector<int>(n, 0));
   int x = 0 , y = 0;
   int d = 0 , i = 1 ;
   int dx[4] = {0, 1, 0, -1};
   int dy[4] = {1, 0, -1, 0};
   while(i <= n * n){
      lin[x][y] = i;
      int nx = x + dx[d];
      int ny = y + dy[d];
      if(nx < 0 || nx >= n || ny < 0 || ny >= n || lin[nx][ny] != 0){
         d = (d + 1) % 4;
         nx = x + dx[d];
         ny = y + dy[d];
      }
      x = nx;
      y = ny;
      i++;
   }
   for(auto s:lin){
      for(auto s1:s){
         cout <<  setw(3) << s1;
      }
      cout << '\n';
   }
   return 0;
}