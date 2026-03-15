#include <iostream>
#include <vector>
using namespace std;
template <class T>
class MyVector{
private:
    vector<T> a;
public:
    MyVector(T b , T c , T d){
        a.push_back(b);
        a.push_back(c);
        a.push_back(d); 
    }
    MyVector( vector<T>& v){ a = v; }
    void merge(vector<T>& v){
        for(auto x : v) a.push_back(x);
    }
    void repeat(){
        vector<T> b;
        for(int i = 0; i < a.size(); i++){
            bool ok = true;
            for(int j = 0; j < b.size(); j++){
                if(a[i] == b[j]){
                    ok = false;
                    break;
                }
            }
            if(ok) b.push_back(a[i]);
        }
        a = b;
    }
    void print(){
        for(auto x : a) cout << x << ' ';
        cout << '\n';
    }
};
int main(){
    vector<int> v1 = {1, 2, 2, 3, 1};
    vector<int> v2 = {3, 4, 4, 5};
    MyVector<int> mv(v1); 
    mv.merge(v2);         
    mv.repeat();          
    mv.print();
    return 0;
}