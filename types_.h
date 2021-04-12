//
// Created by zacky on 4/12/2021.
//

#ifndef POOL_TYPES__H
#define POOL_TYPES__H
// RADIUS CONSTANT IS ONE

// defines all the typedefs
typedef float Pixel;
typedef int Degree;

// if its solid or stripe
enum ballType{
    SOLID = 0,
    STRIPE = 1,
};

// the initial power of the ball
// it will correspond to the starting pixel value
enum power{
    ONE = 10,
    TWO = 20,
    THREE = 30,
    FOUR = 40,
    FIVE = 50,

};


#endif //POOL_TYPES__H
