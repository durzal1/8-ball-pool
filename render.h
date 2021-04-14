//
// Created by kevin on 4/13/2021.
//



#ifndef POOL_RENDER_H
#define POOL_RENDER_H

#include <iostream>

#include <SDL2/SDL.h> // works for kevin too now :D
#include "ball.h"


// TODO make render class

class render {
public:
	// draws circle
	int drawCircle(SDL_Renderer* renderer, ball ball, int radius, bool fill);
};




#endif //POOL_RENDER_H
