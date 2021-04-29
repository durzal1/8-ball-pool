//
// Created by zacky on 4/19/2021.
//
#include "goal.h"
#include <iostream>



// constructor
goal::goal(Pixel x, Pixel y, int Radius) {
    this->x = x;
    this->y = y;
    this->Radius = Radius;
}

// returns point
SDL_Point goal::getPixels() {
    return SDL_Point({ int(x), int(y) });
}

bool goal::isGoal(Pixel bx, Pixel by, int r) {

    // |sqrt((px - bx)^2 + (py - by)^2 - r| gives distance between point (center of goal)
    // and circle we need to see if it is approaching zero. Since we have two sides of the
    // equation to check if it is < 650 (threshold value), we do not the sqrt operation (costly
    // operation)!
     
    int f = fabs(powf(x - bx, 2) + powf(y - by, 2) - r);


    return fabs(powf(x - bx, 2) + powf(y - by, 2) - r) < 650;
}
