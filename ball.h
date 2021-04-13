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

    // if the ball is collided
    bool collided = false;

    // direction the ball collided with the wall
    DIRECTION ColWall;

    // if its solid or stripe or black
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
    void move(std::vector<ball> balls);

    // sees if the ball has collided with another ball
    bool checkForCollisionBall(ball ball);

    // sees if the ball has collided with a wall
    bool checkForCollisionWall(ball ball);

    // if the ball has collided with another ball
    void collisionBall(ball ball1);

    // if a ball has collided with the wall
    void collisionWall(ball ball);

    // calculates vector of the ball's circumference using radius
    void calculateCircumference();

    // returns vector of circumference
    
    std::vector<std::vector<Pixel>> getCir();
};











#endif //POOL_BALL_H
