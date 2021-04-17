#include <iostream>
#include <functional>
// for zacky
// #include "ball.cpp"
// #include "render.cpp"

// for kevin
#include "ball.h"
#include "render.h"


#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {

	// y starting pos needs to be > 60 or else bugs occur
	ball Ballmain = ball(500.0f, 400.0f, TWO, 270, SOLID, 0, 0, 0);
	render Rendermain = render();

	ball Ball2 = ball(730.0f, 500.0f, FIVE, 270, SOLID, 1, 0, 0);
	std::vector<std::reference_wrapper<ball>> balls = { Ballmain, Ball2 };




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

		// MOVE
		Ballmain.move(balls);
		Ball2.move(balls);


		// ADD COLLISION WITH MULTIPLE BALLS LATER
		if (Ballmain.checkForCollisionBall(Ball2)) {
			Ballmain.collisionBall(Ball2);

		}
		

		// sets bg to pink
		SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);

		SDL_RenderClear(renderer);

		

		// goes through each ball to see if one their velocities is over 0

		Rendermain.drawCircle(renderer, Ballmain, 30, true);
		Rendermain.drawCircle(renderer, Ball2, 30, true);

		
		
		
		// draws circles


		SDL_RenderPresent(renderer);


		Uint32 frametime = SDL_GetTicks() - framestart;
		if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);

		/*

		// moves the balls

		// removes one from the velocity
		Ballmain.velocity -= 1;

		//todo to make this more effeicient for training in move just multiply the movement by new x and y by the velocity
		for (int i = 0; i < Ballmain.velocity; i++) {
			// sets bg to pink
			SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);

			SDL_RenderClear(renderer);

			// moves the main ball
			Ballmain.move(balls);

			// goes through each ball to see if one their velocities is over 0
			for (ball& Ball : balls) {
				if (Ball.velocity > 0) {
					// moves the ball
					Ball.move(balls);

					// decreases velocity
					Ball.velocity -= 1;
				}
				Rendermain.drawCircle(renderer, Ball, 30, true);
			}
			// draws circles
			Rendermain.drawCircle(renderer, Ballmain, 30, true);


			SDL_RenderPresent(renderer);
		}
		SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);

		SDL_RenderClear(renderer);

		// does other balls if first ball stops
		for (ball& Ball : balls) {
			if (Ball.velocity > 0) {
				// sets bg to pink


				// moves the ball
				Ball.move(balls);

				// decreases velocity
				Ball.velocity -= 1;

			}
			Rendermain.drawCircle(renderer, Ball, 30, true);
		}
		Rendermain.drawCircle(renderer, Ballmain, 30, true);

		SDL_RenderPresent(renderer);


		//todo this is not computing efficent at all, so change all of this latero n

		*/
	}




	return 0;
}
