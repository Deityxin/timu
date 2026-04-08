#include <iostream>
#include <stdexcept>
using namespace std;
template <class T>
class MyVector {
private:
    static const int MAXN = 1000;
    T data[MAXN];
    int len;
public:
    MyVector() : len(0) {}

    MyVector(int n, const T& value = T()) : len(0) {
        if (n > MAXN) n = MAXN;
        len = n;
        for (int i = 0; i < len; ++i) data[i] = value;
    }
    MyVector(const MyVector& other) : len(other.len) {
        for (int i = 0; i < len; ++i) data[i] = other.data[i];
    }
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            len = other.len;
            for (int i = 0; i < len; ++i) data[i] = other.data[i];
        }
        return *this;
    }
    int size() const {
        return len;
    }
    T& operator[](int pos) {
        return data[pos];
    }
    const T& operator[](int pos) const {
        return data[pos];
    }
    T& at(int pos) {
        if (pos < 0 || pos >= len) throw out_of_range("MyVector::at");
        return data[pos];
    }
    const T& at(int pos) const {
        if (pos < 0 || pos >= len) throw out_of_range("MyVector::at");
        return data[pos];
    }
    T& front() {
        return data[0];
    }
    const T& front() const {
        return data[0];
    }
    T& back() {
        return data[len - 1];
    }
    const T& back() const {
        return data[len - 1];
    }
    void push_back(const T& x) {
        if (len < MAXN) data[len++] = x;
    }
    void pop_back() {
        if (len > 0) --len;
    }
    void insert(int pos, const T& x) {
        if (pos < 0 || pos > len || len >= MAXN) return;
        for (int i = len; i > pos; --i) data[i] = data[i - 1];
        data[pos] = x;
        ++len;
    }
    void erase(int pos) {
        if (pos < 0 || pos >= len) return;
        for (int i = pos; i + 1 < len; ++i) data[i] = data[i + 1];
        --len;
    }
    void clear() {
        len = 0;
    }
    void sort() {
        for (int i = 0; i < len - 1; ++i) {
            for (int j = 0; j < len - 1 - i; ++j) {
                if (data[j] > data[j + 1]) swap(data[j], data[j + 1]);
            }
        }
    }
    int binary_search(const T& x) const {
        int l = 0, r = len - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (data[mid] == x) return mid;
            if (data[mid] < x) l = mid + 1;
            else r = mid - 1;
        }
        return -1;
    }
};
int main() {
    MyVector<int> a;
    for (int i = 5; i >= 1; --i) a.push_back(i);
    MyVector<int> b(3, 7);
    MyVector<int> c(a);
    MyVector<int> d;
    d = b;
    cout << a.size() << endl;
    cout << a.front() << ' ' << a.back() << endl;
    cout << a.at(2) << endl;
    a.insert(2, 10);
    a.erase(1);
    a.pop_back();
    a.sort();
    for (int i = 0; i < a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;
    cout << a.binary_search(10) << endl;
    cout << c.size() << endl;
    cout << d.size() << endl;
    a.clear();
    cout << a.size() << endl;
    return 0;
}