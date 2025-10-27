#ifndef     VECTOR_HPP
#define     VECTOR_HPP

#include <string>

// float type, 2Dvector
class Vec2f {
private:
    float x;
    float y;
public:
    // constructor
    Vec2f(float _x=0.0F, float _y=0.0F) : x(_x), y(_y) {}
    
    // setter
    void setX(float _x) {x = _x;}
    void setY(float _y) {y = _y;}
    
    // getter
    float getX() const {return x;}
    float getY() const {return y;}

    // operator overloading
    Vec2f operator+(const Vec2f other) const;
    Vec2f operator-(const Vec2f other) const;
    Vec2f operator*(float k) const;
    friend Vec2f operator*(float k, Vec2f other);

    Vec2f &operator+=(const Vec2f &other);
    Vec2f &operator-=(const Vec2f &other);
    Vec2f &operator*=(float k);

    // norm
    float norm() const;

    // print
    void print(std::string name) const;
};

#endif  //  VECfloatOR_HPP