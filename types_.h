//
// Created by zacky on 4/12/2021.
//

#ifndef POOL_TYPES__H
#define POOL_TYPES__H
// RADIUS CONSTANT
int Radius = 1;

// threshold distance between two balls to be considered a collision
int ThresDist = 2;

// x and y max constant in pixels
int XMAX = 1000;
int YMAX = 1000;

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
    ONE = 10,
    TWO = 20,
    THREE = 30,
    FOUR = 40,
    FIVE = 50,

};


#endif //POOL_TYPES__H
