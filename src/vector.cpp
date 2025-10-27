#include "vector.hpp"
#include <cmath>
#include <iostream>
#include <string>

// 和
Vec2f Vec2f::operator+(const Vec2f other) const {
    Vec2f res(0.0, 0.0);
    res.setX(x + other.x);
    res.setY(y + other.y);
    return res;
}

// 差
Vec2f Vec2f::operator-(const Vec2f other) const {
    Vec2f res(0.0, 0.0);
    res.setX(x - other.x);
    res.setY(y - other.y);
    return res;
}

// スカラ倍
Vec2f Vec2f::operator*(float k) const {
    return Vec2f(x*k, y*k);
}
Vec2f operator*(float k, const Vec2f other) {
    return Vec2f(other.x*k, other.y*k);
}

// 複合代入演算子
Vec2f &Vec2f::operator+=(const Vec2f &other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vec2f &Vec2f::operator-=(const Vec2f &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2f &Vec2f::operator*=(float k) {
    x *= k;
    y *= k;
    return *this;
}

// ノルム
float Vec2f::norm() const {
    return static_cast<float>(hypot(x, y));
}

// 成分表示
void Vec2f::print(std::string name) const {
    std::cout << name << std::endl;
    std::cout << "(" << x << ", " << y << ")\n";
}