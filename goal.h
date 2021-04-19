//
// Created by zacky on 4/19/2021.
//

#ifndef POOL_GOAL_H
#define POOL_GOAL_H

#include "types_.h"
#include <SDL2/SDL.h>

class goal{
public:
    // x and y coords
    Pixel x;
    Pixel y;

    // Radius
    int Radius;

    // constructor
    goal(Pixel x, Pixel y, int Radius);

    // returns point
    SDL_Point getPixels();





};





#endif //POOL_GOAL_H
