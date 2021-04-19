//
// Created by zacky on 4/12/2021.
//

#ifndef POOL_TYPES__H
#define POOL_TYPES__H



// defines all the typedefs
typedef float Pixel;
typedef int Degree;
typedef float Dist;
// if its solid or stripe or other
enum ballType{
    SOLID = -1,
    BLACK = 0,
    STRIPE = 1,
    WHITE = 2,
};
// direction of the wall
enum DIRECTION{
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
};
// the initial power of the ball
// it will correspond to the starting pixel value
enum power{
    NONE = 0,
    ONE = 1,
    TWO = 2,
    THREE = 4,
    FOUR = 6,
    FIVE = 8,
    SIX = 10,

};


#endif //POOL_TYPES__H
