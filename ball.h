//
// Created by zacky on 4/12/2021.
//
#ifndef POOL_BALL_H
#define POOL_BALL_H
#include "vector"
#include "types_.h"
#include <iostream>
class ball{
    // x and y cords
    Pixel x;
    Pixel y;

    // if its solid or stripe
    ballType BallType;

    // vector that stores the x and y of each pixel of the circumference
    std::vector<std::vector<Pixel>> circumference;

    // how many pixels it is currently going per rotation
    // a rotation here is defined by when the ball is done moving the x amount and it about to decrease that x amount by one
    int velocity;

    // direction the ball is currently moving (WILL BE A DEGREE)
    Degree angle;

public:
    // constructor
    ball(Pixel x, Pixel y, power velocity, Degree angle, ballType Balltype);

    // moving function
    void move();
};











#endif //POOL_BALL_H
