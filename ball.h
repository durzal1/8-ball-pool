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



private:
    // if the ball is collided
    bool collided = false;

    // direction the ball collided with the wall
    DIRECTION ColWall = NONE1;

    // vector that stores the x and y of each pixel of the circumference
    std::vector<std::vector<Pixel>> circumference;

    // x and y of last frame
    Pixel lastX;
    Pixel lastY;



public:


    // to not have duplicate innovations
    static int nextInnovation;

    // innovation of the ball that collided with another ball ( ball 1 -> ball 2 it would be ball 1) FROM LAST COLLISION
    static int ballCollInno;

    // if the ball is stuck
    bool isStuck = false;

    // if its solid or stripe or black
    ballType BallType;

    // identification number for the side balls
    int innovation;

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

    // if the ball has made it into a goal
    bool inGoal = false;

    // if the ball had a collision at some point
    bool hadCollision = false;

    // constructor
    ball(Pixel x, Pixel y, power p, ballType Balltype, float velx, float vely);

    // moving function
    void move(std::vector<SDL_Rect> rects, int HEIGHT, goal Goal, std::vector<SDL_Point> points, int frame);

    // sees if the ball has collided with another ball
    bool checkForCollisionBall(ball& ball);

    // handles ball collision with walls
    bool collisionAllWalls(std::vector<SDL_Rect> rects, int HEIGHT, goal Goal, std::vector<SDL_Point> points);

    // if the ball has collided with another ball
    void collisionBall(ball& ball1);

    // fixes overlapping
    void fixOverlapping();
    void fixOverlappingFinal();

    // returns x, y
    SDL_Point getPixels();

    // returns color
    SDL_Color getColor();
};












#endif //POOL_BALL_H
