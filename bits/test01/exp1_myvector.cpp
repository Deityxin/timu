#include <iostream>
using namespace std;
template <typename T>
class MyVector {
private:
    T* data;
    int len;
    int cap;
    void expand() {
        int new_cap;
        if (cap == 0) new_cap = 1;
        else new_cap = cap * 2;

        T* p = new T[new_cap];
        for (int i = 0; i < len; i++) p[i] = data[i];

        delete[] data;
        data = p;
        cap = new_cap;
    }
public:
    MyVector() {
        data = nullptr;
        len = 0;
        cap = 0;
    }
    MyVector(int n, const T& value = T()) {
        len = n;
        cap = n;
        if (cap == 0) data = nullptr;
        else {
            data = new T[cap];
            for (int i = 0; i < len; i++) data[i] = value;
        }
    }
    MyVector(const MyVector& other) {
        len = other.len;
        cap = other.cap;
        if (cap == 0) data = nullptr;
        else {
            data = new T[cap];
            for (int i = 0; i < len; i++) data[i] = other.data[i];
        }
    }
    MyVector(MyVector&& other) {
        data = other.data;
        len = other.len;
        cap = other.cap;
        other.data = nullptr;
        other.len = 0;
        other.cap = 0;
    }
    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;

        delete[] data;
        len = other.len;
        cap = other.cap;
        if (cap == 0) data = nullptr;
        else {
            data = new T[cap];
            for (int i = 0; i < len; i++) data[i] = other.data[i];
        }
        return *this;
    }
    MyVector& operator=(MyVector&& other) {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        len = other.len;
        cap = other.cap;
        other.data = nullptr;
        other.len = 0;
        other.cap = 0;
        return *this;
    }
    ~MyVector() {
        delete[] data;
    }
    int size() const {
        return len;
    }
    T& operator[](int index) {
        return data[index];
    }
    const T& operator[](int index) const {
        return data[index];
    }
    T& at(int index) {
        if (index < 0 || index >= len) {
            cout << "index out of range\n";
            exit(0);
        }
        return data[index];
    }
    const T& at(int index) const {
        if (index < 0 || index >= len) {
            cout << "index out of range\n";
            exit(0);
        }
        return data[index];
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
    void push_back(const T& value) {
        if (len == cap) expand();
        data[len] = value;
        len++;
    }
    void pop_back() {
        if (len > 0) len--;
    }
    void insert(int index, const T& value) {
        if (index < 0 || index > len) return;
        if (len == cap) expand();
        for (int i = len; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        len++;
    }
    void erase(int index) {
        if (index < 0 || index >= len) return;
        for (int i = index; i + 1 < len; i++) {
            data[i] = data[i + 1];
        }
        len--;
    }
    void clear() {
        len = 0;
    }
};
int main() {
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.insert(1, 15);
    v.erase(2);
    v.pop_back();
    cout << "size = " << v.size() << '\n';
    cout << "front = " << v.front() << ", back = " << v.back() << '\n';
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << (i + 1 == v.size() ? '\n' : ' ');
    }
    MyVector<int> a(v);
    MyVector<int> b;
    b = static_cast<MyVector<int>&&>(a);
    cout << "moved size = " << b.size() << '\n';
    return 0;
}
