#include <iostream>
using namespace std;
class Circle {
private:
    double m_r;
public:
    Circle(double r = 1.0) : m_r(r) {
        if (r <= 0) {
            cerr << "警告：半径应为正数，已自动设为默认值1.0" << endl;
            m_r = 1.0;
        }
    }
    void setR(double r) {
        if (r > 0) m_r = r;
        else cerr << "设置失败：半径必须为正数！" << endl;
    }
    double getR() const { 
        return m_r; 
    }
    double area() const { 
        return 3.14159 * m_r * m_r; 
    }
    double circumference() const { 
        return 2 * 3.14159 * m_r; 
    }
    void display() const {
        cout << "----- 圆信息 -----" << endl;
        cout << "半径: " << m_r << " 单位" << endl;
        cout << "面积: " << area() << " 平方单位" << endl;
        cout << "周长: " << circumference() << " 单位" << endl;
        cout << "------------------" << endl;
    }
};

int main() {
    Circle circle1;
    cout << ">> 创建默认圆对象：" << endl;
    circle1.display();
    Circle circle2(2.5); // 半径2.5
    cout << ">> 创建半径2.5的圆：" << endl;
    circle2.display();
    circle1.setR(3.0);
    cout << ">> 修改后半径: " << circle1.getR() << endl;
    circle1.display();
    cout << ">> 测试非法半径设置：" << endl;
    Circle invalidCircle(-5);
    invalidCircle.setR(-1); 
    invalidCircle.display();  
    return 0;
}
