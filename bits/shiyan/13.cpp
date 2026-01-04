#include <iostream>
using namespace std;

class Complex {
private:
    double real; // 实部
    double imag; // 虚部

public:
    // (1) 默认构造函数：创建一个实部和虚部都为0的复数 (0+0i)
    Complex() : real(0), imag(0) {
        cout << "默认构造函数被调用，创建了 0+0i" << endl;
    }

    // (2) 带参数的构造函数：用给定的实部和虚部创建复数
    Complex(double r, double i) : real(r), imag(i) {
        cout << "带参构造函数被调用，创建了 " << r << "+" << i << "i" << endl;
    }

    // (3) 复制构造函数：用一个已存在的Complex对象来初始化新对象
    Complex(const Complex& other) : real(other.real), imag(other.imag) {
        cout << "复制构造函数被调用，从 (" << other.real << "+" << other.imag << "i) 创建了新对象" << endl;
    }

    // (4) 析构函数：对象销毁时自动调用（这里没有动态资源要释放，所以函数体是空的，但输出信息用于演示）
    ~Complex() {
        cout << "析构函数被调用，销毁了 " << real << "+" << imag << "i" << endl;
    }

    // (5) 设置实部
    void setReal(double r) {
        real = r;
    }

    // (6) 设置虚部
    void setImag(double i) {
        imag = i;
    }

    // (7) 获取实部（虽然不是要求，但通常也会提供获取函数）
    double getReal() const {
        return real;
    }

    // (8) 获取虚部
    double getImag() const {
        return imag;
    }

    // (9) 重载输出运算符 <<
    // 声明为友元函数，这样它才能直接访问类的私有成员 real 和 imag
    friend ostream& operator<<(ostream& os, const Complex& c);
};

// (10) 实现重载的输出运算符 <<
// 这个函数负责处理格式：如 3.1+2.5i, 3.1-2.5i, 5.0, 2.5i 等
ostream& operator<<(ostream& os, const Complex& c) {
    // 先处理实部：如果实部不为0，或者实部虚部都为0，就输出实部
    if (c.real != 0 || c.imag == 0) {
        os << c.real;
    }

    // 再处理虚部
    if (c.imag != 0) {
        // 决定虚部前面的符号
        if (c.imag > 0 && c.real != 0) { // 如果虚部为正且实部不为0，需要输出一个'+'
            os << "+";
        }
        // 如果虚部是负数，运算符<<会自动输出负号，所以我们不需要额外处理

        // 输出虚部。如果虚部的绝对值是1，则省略数字1，只输出 'i' 或 '-i'
        if (c.imag == 1) {
            os << "i";
        } else if (c.imag == -1) {
            os << "-i";
        } else {
            os << c.imag << "i";
        }
    }
    return os; // 返回输出流对象，支持连续输出，如 cout << c1 << " " << c2;
}

// (11) 主函数：测试我们实现的所有功能
int main() {
    cout << "=== 测试构造函数 ===" << endl;
    Complex c1;             // 调用默认构造函数
    Complex c2(3.1, 2.5);   // 调用带参构造函数
    Complex c3 = c2;        // 调用复制构造函数

    cout << "\n=== 测试设置函数 ===" << endl;
    c1.setReal(5.0);
    c1.setImag(-1.0); // 设置一个负的虚部

    cout << "\n=== 测试输出运算符 << ===" << endl;
    cout << "c1: " << c1 << endl;   // 应输出 5-i
    cout << "c2: " << c2 << endl;   // 应输出 3.1+2.5i
    cout << "c3: " << c3 << endl;   // 应输出 3.1+2.5i

    cout << "\n=== 测试更多输出格式 ===" << endl;
    Complex c4(0, 1);  // 纯虚数
    Complex c5(2, 0);  // 实数
    Complex c6(0, 0);   // 零
    Complex c7(4, -2); // 虚部为负
    Complex c8(-1, -1); // 实部虚部都为负

    cout << "c4: " << c4 << endl; // 应输出 i
    cout << "c5: " << c5 << endl; // 应输出 2
    cout << "c6: " << c6 << endl; // 应输出 0
    cout << "c7: " << c7 << endl; // 应输出 4-2i
    cout << "c8: " << c8 << endl; // 应输出 -1-i

    cout << "\n=== main函数结束，析构函数将被自动调用 ===" << endl;
    // 当main函数结束时，所有局部对象c1, c2, c3...都会被销毁，它们的析构函数会被调用
    return 0;
}
