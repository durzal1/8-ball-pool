//
// Created by zacky on 4/12/2021.
//
#ifndef POOL_BALL_H
#define POOL_BALL_H
#include "vector"
#include "types_.h"
#include <iostream>
#include <SDL2/SDL.h>

#include "goal.h"


class ball {
//
  

private:
    // if the ball is collided
    bool collided = false;

    // direction the ball collided with the wall
    DIRECTION ColWall = NONE1;

    // if its solid or stripe or black
    ballType BallType;

    // vector that stores the x and y of each pixel of the circumference
    std::vector<std::vector<Pixel>> circumference;

    // identification number for the side balls
    int innovation;
    
    // to not have duplicate innovations
    static int nextInnovation;

public:


    // contains all balls as they are created
    static std::vector<std::reference_wrapper<ball>> balls;
    

    // input power
    power initialPower;

    // RADIUS CONSTANT
    int Radius = 20;

    // x and y cords
    Pixel x;
    Pixel y;

    // velocities
    float velx;
    float vely;

    // mass
    float mass;
    
    // acceleration
    float ax, ay;

    // frames since last wall collision
    int FrameSinceLast = 4;

    // if it hits the wall at a wierd angle
    bool WierdAngle = false;

    // helps with clip bugs
    int count_left = 0;
    bool goLeft = true;
    bool goUpDown = true;
    bool goRight = true;

    // constructor
    ball(Pixel x, Pixel y, power p, ballType Balltype, float velx, float vely);

    // moving function
    void move(std::vector<SDL_Rect> rects, int HEIGHT, goal Goal, std::vector<SDL_Point> points);

    // sees if the ball has collided with another ball
    bool checkForCollisionBall(ball& ball);

    // sees if the ball has collided with a wall
    bool checkForCollisionWall(std::vector<SDL_Rect> rects, int HEIGHT, goal Goal, std::vector<SDL_Point> points);

    // if the ball has collided with another ball
    void collisionBall(ball& ball1);

    // if a ball has collided with the wall
    void collisionWall();


    // returns x, y
    SDL_Point getPixels();

    // returns color
    SDL_Color getColor();
};












#endif //POOL_BALL_H
