//
// Created by zacky on 4/12/2021.
//

#include "ball.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include <SDL2/SDL.h>

// RADIUS CONSTANT
int Radius = 30;

// Radius for movement (should always be one)
int MoveRad = 1;

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
void ball::move(std::vector<ball> balls) {;
    // removes one from the velocity
    velocity -= 1;
    for (int i = 0; i < velocity; i ++){

        // calculates the new x and y
        x += MoveRad * cos(angle * M_PI / 180);
        y += MoveRad * sin(angle * M_PI / 180);

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

        // stops for a little bit
        SDL_Delay(0);
    }
}
//function that will check if a collision has occurred with another ball
bool ball::checkForCollisionBall(ball ball_) {

    // distance between each balls
    Dist dist = pow((ball_.x - this->x), 2) + pow((this->y- ball_.y), 2);

    // threshold
    float ThresDist = pow((Radius * 2),2);
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
    // get the angle between the two balls
    float delta_x = ball1.x - this->x ;
    float delta_y = ball1.y - this->y ;

    float theta_radians = atan2(delta_y, delta_x);

    //gets degrees
    int Deg1 = theta_radians * 180/M_PI;

    // from the ball thats being collided into's perspective

    float delta2_x = this->x - ball1.x;
    float delta2_y = this->y - ball1.y;

    float theta2_radians = atan2(delta2_y, delta2_x);

    int Deg2 = theta2_radians * 180/M_PI;

    // mass of both object ( both 1 because they're the same)
    int m1 = 1;
    int m2 = 1;

    //    int b_vel = this->velocity * ((sqrt(m1 + m2 + (2 * m1 * m2 * cos(theta_radians))) ) / (m1+ m2) );
    //    int b1_vel = this->velocity * ((2 * m1) / (m1 + m2)) * sin(theta_radians/2);

    // gets the new velocity of each ball
    int v1 = (this->velocity * (m1 - m2) + (2 * m2 * 0)) / (m1 + m2);
    int v2 = (0 * (m2-m1) + (2 * m1 * this->velocity)) / (m1 + m2) ;

    //todo set the ball to a wierd angle for it to collide then test

    // gets the new direction of each ball
    float d1 = ((m2 * sin(theta_radians)) / (m1 + (m2 * cos(theta_radians))));
    float d2 = (M_PI - theta2_radians) / 2;

    // convert to degrees
    int d1_deg = d1 * 180/M_PI;
    int d2_deg = d2 * 180/M_PI;

    ball1.velocity = this->velocity - (this->velocity / 4);
    this->velocity = this->velocity / 4;



}

// function returns vector of the ball's circumference relative to x, y using radius
void ball::calculateCircumference() {
    // clears circumference
    circumference.clear();

    // cycles through 360 degrees
    for (int angle = 1; angle < 361; angle++) {
        float x = (float)(Radius * cos(angle * M_PI / 180)) + this->x;
        float y = (float)(Radius * sin(angle * M_PI / 180)) + this->y;
        // adds to vector of vector
        circumference.push_back({ x, y });
    }
};

// returns ball circumference coordinates
std::vector<std::vector<Pixel>> ball::getCir() {
    return this->circumference;
};

// clears vector
void ball::clearCir() {
    this->circumference.clear();
};

// changes x, y (for testing)
void ball::moveOffset(int x, int y) {
    this->x += x;
    this->y += y;
}


// returns point
SDL_Point ball::getPixels() {
    return SDL_Point({ (int)this->x, (int)this->y });
}


// returns color
SDL_Color ball::getColor() {
    SDL_Color color = {};

 
    switch (this->BallType)
    {
    case SOLID:           
        color = { 20, 39, 255 }; //  blue for now
        break;
    case BLACK:
        color = { 0, 0, 0 };
        break;
    case STRIPE:
        color = { 255, 165, 0 }; // orange for now
        break;
    case WHITE:
        color = { 255, 255, 255 };
    default:
        break;
    }

    return color;
}
