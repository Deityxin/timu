#include <iostream>
using namespace std;
class cylinder{
    double m_radious, m_height;
public:
    double new_r(){
        int x ;
        cin >> x;
        return m_radious = x;
    }
    double surface(){
        return (3.14 * m_radious * m_radious)*2 + (2 * 3.14 * m_radious * m_height);
    }
    double volume(){
        return 3.14 * m_radious * m_radious * m_height;
    }
    double geometric(){
        double a;
        cin >> a;
        double new_radious = a * m_radious;
        double new_height = a * m_height;
        return 3.14 * new_radious * new_radious * new_height;
    }
    cylinder (double i = 0, double h = 0): m_radious(i) , m_height(h){}
};
int main (){
    cylinder object(1.0 , 1.0);
    double vol = object.volume();
    cout << vol << endl;
    return 0;
}