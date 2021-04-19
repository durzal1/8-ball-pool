//
// Created by zacky on 4/19/2021.
//
#include "goal.h"


// constructor
goal::goal(Pixel x, Pixel y, int Radius){
    this->x = x;
    this->y = y;
    this->Radius = Radius;
}

// returns point
SDL_Point goal::getPixels() {
    return SDL_Point({int(x), int(y)});
}