//
// Created by zacky on 4/28/2021.
//

#ifndef POOL_VECTOR2F_H
#define POOL_VECTOR2F_H

struct Vector2f{

    float x,y;

    Vector2f operator-(Vector2f B){
        return {x - B.x, y - B.y};
    }

    Vector2f& operator*=(float scalar){
        x *= scalar;
        y *= scalar;
        return *this;
    }

    float operator~(){
        return sqrt(x * x + y * y);
    }

    void normalise(){
        (*this) *= 1.0 / ~(*this);
    }


};

#endif //POOL_VECTOR2F_H
