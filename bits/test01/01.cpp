#include <iostream>
using namespace std;
class Celestial {
protected:
    double m_mass;  
    double m_radius; 
public:
    Celestial(double mass = 0.0, double radius = 0.0) 
        : m_mass(mass), m_radius(radius) {
        cout << "Celestial constructed\n";
    }
    Celestial(const Celestial& other) 
        : m_mass(other.m_mass), m_radius(other.m_radius) {
        cout << "Celestial copy constructed\n";
    }
    Celestial& operator=(const Celestial& other) {
        if (this == &other) return *this;
        m_mass = other.m_mass;
        m_radius = other.m_radius;
        cout << "Celestial assigned\n";
        return *this;
    }
    virtual ~Celestial() {
        cout << "Celestial destructed\n";
    }
};
class Planet : public Celestial {
private:
    Celestial m_satellite;

public:
    Planet(double mass = 0.0, double radius = 0.0, 
           const Celestial& satellite = Celestial()) 
        : Celestial(mass, radius), m_satellite(satellite) {
        cout << "Planet constructed\n";
    }
    Planet(const Planet& other) 
        : Celestial(other), m_satellite(other.m_satellite) {
        cout << "Planet copy constructed\n";
    }
    Planet& operator=(const Planet& other) {
        if (this == &other) return *this;
        Celestial::operator=(other);       
        m_satellite = other.m_satellite;     
        cout << "Planet assigned\n";
        return *this;
    }
    virtual ~Planet() {
        cout << "Planet destructed\n";
    }
};
