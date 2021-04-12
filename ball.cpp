//
// Created by zacky on 4/12/2021.
//

#include "ball.h"
#include <cmath>
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
        }
        // collides with wall
        if (checkForCollisionWall()){
            collisionWall();
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
bool ball::checkForCollisionWall() {
    // left wall
    if (x < 0){
        this->ColWall = LEFT;
        return true;
    }
    // up wall
    else if (y > YMAX){
        this->ColWall = UP;
        return true;
    }
    // right wall
    else if(x > XMAX){
        this->ColWall = RIGHT;
        return true;
    }
    //down wall
    else if (y < 0){
        this->ColWall = DOWN;
        return true;
    }
    return false;
}
// function that will happen if a collision occurred with a wall
void ball::collisionWall(){
    // these numbers should be experimented with
    this->velocity /= 3;

    // depending on what direction it is facing
    switch (this->ColWall){
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