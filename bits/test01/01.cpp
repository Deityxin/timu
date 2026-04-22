 #include <iostream>
 #include <vector>
 using namespace std;
 template <typename T>
 void xuan(vector<T> &tem) {
   for (int i = 0; i + 1 < tem.size(); ++i) {
      int pos = i;
      for (int j = i + 1; j < tem.size(); ++j) {
         if (tem[j] < tem[pos]) pos = j;
      }
      if (pos != i) swap(tem[i], tem[pos]);
   }
 }
 int main() {
   vector<int> tem;
   for (int i = 0 , x; i < 5; ++i){cin >> x; tem.push_back(x);}
   xuan(tem);
   for(int a : tem){cout << a << ' ';}
   cout << '\n';
   return 0;
 }