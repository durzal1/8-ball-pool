//
// Created by zacky on 4/12/2021.
//
#ifndef POOL_BALL_H
#define POOL_BALL_H
#include "vector"
#include "types_.h"
#include <iostream>
#include <SDL2/SDL.h>



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

    // identification number for the side balls
    int innovation;

    // direction the ball is currently moving (WILL BE A DEGREE)
    Degree angle;

public:
    // how many pixels it is currently going per rotation
    // a rotation here is defined by when the ball is done moving the x amount and it about to decrease that x amount by one
    int velocity;

    // constructor
    ball(Pixel x, Pixel y, power velocity, Degree angle, ballType Balltype, int innovation);

    // moving function
    void move(std::vector<ball> &balls);

    // sees if the ball has collided with another ball
    bool checkForCollisionBall(ball& ball);

    // sees if the ball has collided with a wall
    bool checkForCollisionWall();

    // if the ball has collided with another ball
    void collisionBall(ball& ball1);

    // if a ball has collided with the wall
    void collisionWall();

    // calculates vector of the ball's circumference using radius
    void calculateCircumference();

    // returns vector of circumference
    std::vector<std::vector<Pixel>> getCir();

    // clears circumference (used to clear so it can draw new pixels after it has moved)
    void clearCir();

    // sets x, y (for testing)
    void moveOffset (int x, int y);

    // returns x, y
    SDL_Point getPixels();

    // returns color
    SDL_Color getColor();
};











#endif //POOL_BALL_H
