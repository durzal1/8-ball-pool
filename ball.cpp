//
// Created by zacky on 4/12/2021.
//

#include "ball.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


// RADIUS CONSTANT
int Radius = 1;

// threshold distance between two balls to be considered a collision
int ThresDist = 2;

// x and y max constant in pixels
int XMAX = 1000;
int YMAX = 1000;


// constructor
ball::ball(Pixel x, Pixel y, power velocity, Degree angle, ballType Balltype) {
    this->x = x;
    this->y = y;
    this->velocity = velocity;
    this->angle = angle;
    this->BallType = Balltype;
}
//moving function
void ball::move(std::vector<ball> balls) {
    for (int i = 0; i < velocity; i ++){
 
        // calculates the new x and y
        x += Radius * cos(angle * M_PI / 180);
        y += Radius * sin(angle * M_PI / 180);
        
        // removes one from the velocity
        velocity -= 1;

        /// if it collides
        // collides with ball
        // for loop for each individual ball
        for(ball Ball:balls) {
            if (checkForCollisionBall(Ball)) {
                collisionBall(Ball);
            }
            // collides with wall
            if (checkForCollisionWall(Ball)) {
                collisionWall(Ball);
            }
        }
        
    }

}
//function that will check if a collision has occurred with another ball
bool ball::checkForCollisionBall(ball ball_) {

    // distance between each balls
    Dist dist = abs(ball_.x - this->x);
    // if the ball is less than or equal to the threshold they are colliding
    if (dist <= ThresDist){
        ball_.collided = true;
        this->collided = true;
        return true;
    }

    return false;
}
// function that will check if a collision has occurred with the wall
bool ball::checkForCollisionWall(ball ball_) {
    // left wall
    if (x < 0){
        ball_.ColWall = LEFT;
        return true;
    }
    // up wall
    else if (y > YMAX){
        ball_.ColWall = UP;
        return true;
    }
    // right wall
    else if(x > XMAX){
        ball_.ColWall = RIGHT;
        return true;
    }
    //down wall
    else if (y < 0){
        ball_.ColWall = DOWN;
        return true;
    }
    return false;
}
// function that will happen if a collision occurred with a wall
void ball::collisionWall(ball ball_){
    // these numbers should be experimented with
    this->velocity /= 3;

    // depending on what direction it is facing
    switch (ball_.ColWall){
        case LEFT: ; break;
        case UP: ; break;
        case RIGHT: ; break;
        case DOWN: ; break;
    }

    // todo change direction
}

// function that will happen if a collision occurred with a ball
void ball::collisionBall(ball ball1) {
    // these numbers should be experimented with

    // changes the velocity of each ball
    ball1.velocity = this->velocity;
    this->velocity /= 3;

    // todo change direction
}