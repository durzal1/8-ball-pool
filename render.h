//
// Created by kevin on 4/13/2021.
//



#ifndef POOL_RENDER_H
#define POOL_RENDER_H

#include <iostream>

//#include <SDL.h> for kevin
#include <SDL2/SDL.h> // for zacky
#include "ball.h"

// TODO make render class

class render {
public:
	// draws circle
	void drawCircle(SDL_Renderer* renderer, ball ball);
};




#endif //POOL_RENDER_H