#include "object.hpp"
#include <cmath>

// オブジェクト同士の衝突判定
bool isCollision(Obj2 om, Obj2 OM) {
    Vec2f distance = om.pos - OM.pos;                           // 物体間の距離ベクトル
    Vec2f deltaDis((om.w()+OM.w())/2.0F, (om.h()+OM.h())/2.0F); // 衝突直後の物体間の距離ベクトル
    
    // 衝突判定
    if((abs(distance.getX()) <= deltaDis.getX()) &&
    (abs(distance.getY()) <= deltaDis.getY())) {
        return true;
    } else {
        return false;
    }
}