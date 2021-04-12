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
void ball::move() {
    for (int i = 0; i < velocity; i ++){
        // calculates the new x and y
        x += cos(angle * M_PI / 180);
        y += sin(angle * M_PI / 180);

        // removes one from the velocity
        velocity -= 1;
    }

}