 #include <iostream>
 #include <vector>
 using namespace std;

 template <typename T>
 void xuan(vector<T> &tem) {
   for (int i = 0; i + 1 < (int)tem.size(); ++i) {
      int pos = i;
      for (int j = i + 1; j < (int)tem.size(); ++j) {
         if (tem[j] < tem[pos]) pos = j;
      }
      if (pos != i) swap(tem[i], tem[pos]);
   }
 }

 int main() {
   int n;
   cin >> n;
   vector<int> tem(n);
   for (int i = 0; i < n; ++i) cin >> tem[i];

   xuan(tem);

   for (int i = 0; i < n; ++i) {
      if (i) cout << ' ';
      cout << tem[i];
   }
   cout << '\n';
   return 0;
 }