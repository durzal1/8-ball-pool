//
// Created by kevin on 4/13/2021.
//



#ifndef POOL_RENDER_H
#define POOL_RENDER_H

#include <iostream>

#include <SDL2/SDL.h>
#include "ball.h"
#include "goal.h"

// TODO make render class

class render {
public:
    // draws circle
    int drawCircle(SDL_Renderer* renderer, ball ball, int radius, bool fill);

    // draws goal
    int drawGoal(SDL_Renderer *renderer,  goal Goal, bool fill);

    // sets the boundary
    std::vector<SDL_Rect>  setBoundary(SDL_Renderer *renderer, int X, int Y, goal Goal);

};



#endif //POOL_RENDER_H
