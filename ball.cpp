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
int XMAX = 900;
int YMAX = 900;


// constructor
ball::ball(Pixel x, Pixel y, power velocity, Degree angle, ballType Balltype, int innovation) {
    this->x = x;
    this->y = y;
    this->velocity = velocity;
    this->angle = angle;
    this->BallType = Balltype;
    this->innovation = innovation;
    this->initial_vel = velocity;
}
//moving function
void ball::move(std::vector<ball>& balls) {

    // calculates the new x and y
    x += MoveRad * cos(angle * M_PI / 180);
    y += MoveRad * sin(angle * M_PI / 180);

    /// if it collides

    // collides with ball
    // for loop for each individual ball
    for (ball& Ball : balls) {
        if (Ball.innovation == innovation) {
            Ball.x = x;
            Ball.y = y;
            continue;
        }
        if (checkForCollisionBall(Ball)) {
            collisionBall(Ball);
        }

    }
    // collides with wall
    if (checkForCollisionWall()) {
        collisionWall();
    }

    // stops for a little bit
    int c = initial_vel - velocity;
    SDL_Delay(c);

}
//function that will check if a collision has occurred with another ball
bool ball::checkForCollisionBall(ball& ball_) {

    // distance between each balls
    Dist dist = pow((ball_.x - this->x), 2) + pow((this->y - ball_.y), 2);

    // threshold
    float ThresDist = pow((Radius * 2), 2);
    // if the ball is less than or equal to the threshold they are colliding
    if (dist <= ThresDist) {
        ball_.collided = true;
        this->collided = true;
        return true;
    }

    return false;
}
// function that will check if a collision has occurred with the wall
bool ball::checkForCollisionWall() {
    // left wall
    if (x - Radius <= 0) {

        ColWall = LEFT;
        return true;
    }
    // up wall
    else if (y + Radius >= YMAX) {
        ColWall = UP;
        return true;
    }
    // right wall
    else if (x + Radius >= XMAX) {
        int l = x + (4 * Radius);
        ColWall = RIGHT;
        return true;
    }
    //down wall
    else if (y - Radius <= 0) {
        ColWall = DOWN;
        return true;
    }
    return false;
}
// function that will happen if a collision occurred with a wall
void ball::collisionWall() {
    Degree org_angle = this->angle;
    float theta_radians;
    // get the angle between the ball and point of collision
    theta_radians = atan2(this->x, this->y);
    float degs = theta_radians * (float)(180 / M_PI); // converts to degrees
    this->angle = org_angle - degs;
    
    
    // old code just in case
    /*
    float theta_radians;
    float theta2_radians;
    if (ColWall == UP) {

        // get the angle between the ball and point of collision
        float delta_x = (this->x) - this->x;
        float delta_y = (this->y + Radius) - this->y;

        theta_radians = atan2(delta_y, delta_x);


        // from the wall thats being collided into's perspective
        float delta2_x = this->x - (this->x);
        float delta2_y = this->y - (this->y + Radius);

        theta2_radians = atan2(delta2_y, delta2_x);

        int Deg2 = theta2_radians * 180 / M_PI;
    }
    else if (ColWall == RIGHT) {
        std::cout << "returning r";
        // get the angle between the ball and point of collision
        float delta_x = (this->x + Radius) - this->x;
        float delta_y = (this->y) - this->y;

        theta_radians = atan2(delta_y, delta_x);

        // from the wall thats being collided into's perspective
        float delta2_x = this->x - (this->x + Radius);
        float delta2_y = this->y - (this->y);

        theta2_radians = atan2(delta2_y, delta2_x);

        int Deg2 = theta2_radians * 180 / M_PI;
    }
    else if (ColWall == LEFT) {
        std::cout << "returning";
        // get the angle between the ball and point of collision
        float delta_x = (this->x - Radius) - this->x;
        float delta_y = (this->y) - this->y;

        theta_radians = atan2(delta_y, delta_x);

        // from the wall thats being collided into's perspective
        float delta2_x = this->x - (this->x - Radius);
        float delta2_y = this->y - (this->y);

        theta2_radians = atan2(delta2_y, delta2_x);

        int Deg2 = theta2_radians * 180 / M_PI;
    }
    else if (ColWall == DOWN) {
        // get the angle between the ball and point of collision
        float delta_x = (this->x) - this->x;
        float delta_y = (this->y - Radius) - this->y;

        theta_radians = atan2(delta_y, delta_x);


        // from the wall thats being collided into's perspective
        float delta2_x = this->x - (this->x);
        float delta2_y = this->y - (this->y - Radius);

        theta2_radians = atan2(delta2_y, delta2_x);

        int Deg2 = theta2_radians * 180 / M_PI;
    }




    // mass of both object ( both 1 because they're the same)
    int m1 = 1;
    int m2 = 1;

    // gets the new velocity of each ball
    int b_vel = this->velocity * ((sqrt(m1 + m2 + (2 * m1 * m2 * cos(theta_radians)))) / (m1 + m2));
    int b1_vel = this->velocity * ((2 * m1) / (m1 + m2)) * sin(theta_radians / 2);

    // gets the new direction of each ball
    float d1 = ((m2 * sin(theta_radians)) / (m1 + (m2 * cos(theta_radians))));
    float d2 = (M_PI - theta2_radians) / 2;

    // convert to degrees
    int d1_deg = tan(d1) * 180 / M_PI;
    int d2_deg = d2 * 180 / M_PI;

    //    this->velocity = 1000;

    this->angle = d2_deg;
    collided = true;
    */
}

// function that will happen if a collision occurred with a ball
void ball::collisionBall(ball& ball1) {
    // get the angle between the two balls
    float delta_x = ball1.x - this->x;
    float delta_y = ball1.y - this->y;

    float theta_radians = atan2(delta_y, delta_x);

    //gets degrees
    int Deg1 = theta_radians * 180 / M_PI;

    // from the ball thats being collided into's perspective

    float delta2_x = this->x - ball1.x;
    float delta2_y = this->y - ball1.y;

    float theta2_radians = atan2(delta2_y, delta2_x);

    int Deg2 = theta2_radians * 180 / M_PI;

    // mass of both object ( both 1 because they're the same)
    int m1 = 1;
    int m2 = 1;

    // gets the new velocity of each ball
    int b_vel = this->velocity * ((sqrt(m1 + m2 + (2 * m1 * m2 * cos(theta_radians)))) / (m1 + m2));
    int b1_vel = abs(this->velocity * ((2 * m1) / (m1 + m2)) * sin(theta_radians / 2));

    // gets the new direction of each ball
    float d1 = (M_PI - theta_radians) / 2;
    float d2 = (M_PI - theta2_radians) / 2;

    // convert to degrees
    int d1_deg = (d1) * 180 / M_PI;
    int d2_deg = d2 * 180 / M_PI;

    ball1.velocity = b_vel;
    this->velocity = b1_vel;

    this->angle = d1_deg;
    ball1.angle = d2_deg;

    ball1.initial_vel = b_vel;



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
