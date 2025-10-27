#ifndef     OBJ_HPP
#define     OBJ_HPP

#include "vector.hpp"

// 2次元の物体
class Obj2 {
private:
    float width;    // 幅[px]
    float hight;    // 高さ[px]
public:
    // 中心位置ベクトル[px]
    Vec2f pos;
    // 中心速度ベクトル[px/s]
    Vec2f vel;

    // constructor
    Obj2(int _w=0, int _h=0) : width(_w), hight(_h) {
        pos = Vec2f();
        vel = Vec2f();
    }
    
    // setter
    void setWidth(float _w) {width = _w;}
    void setHight(float _h) {hight = _h;}

    // getter
    float w() const {return width;}
    float h() const {return hight;}
};

// オブジェクト同士の衝突判定
bool isCollision(Obj2 om, Obj2 OM);

#endif  //  OBJ_HPP