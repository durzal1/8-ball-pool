#include <iostream>
#include <functional>
// for zacky
// #include "ball.cpp"
// #include "render.cpp"

// for kevin
#include "ball.h"
#include "render.h"


#include <SDL2/SDL.h>


// initializes innovation
int ball::nextInnovation = 0;

// initializes vector of all balls
std::vector<std::reference_wrapper<ball>> ball::balls = {};

int main(int argc, char* argv[]) {

	// creates renderer, balls

	render Rendermain = render();
	ball Ballmain = ball(500.0f, 60.0f, TWO, SOLID, 500, 300);
	ball Ball2 = ball(730.0f, 300.0f, FIVE, SOLID, 0, 0);
	ball Ball3 = ball(850.0f, 200.0f, FIVE, BLACK, 0, 0);


	



	// initializes SDL


	SDL_Window* win = NULL;
	SDL_Renderer* renderer = NULL;



	int posX = 100, posY = 100, width = 900, height = 900;

	SDL_Init(SDL_INIT_VIDEO);

	win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


	Uint32 framestart;

	while (true) {
		framestart = SDL_GetTicks();


		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(win);

				SDL_Quit();
				break;
			}
		}

		// moves every ball

		for (ball& b : ball::balls) b.move();


		



		// sets bg to pink
		SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);


		// clears screen
		SDL_RenderClear(renderer);



		// goes through each ball and draws it

		for (ball& b : ball::balls) {
			Rendermain.drawCircle(renderer, b, 30, true);
		}



		// presents screen
		SDL_RenderPresent(renderer);


		// sets framerate to 144 by delaying each frame if needed
		Uint32 frametime = SDL_GetTicks() - framestart;
		if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);

	
	}




	return 0;
}
