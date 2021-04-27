#include <iostream>
#include <functional>
// for zacky
//#include "ball.cpp"
//#include "render.cpp"
//
// for kevin
#include "ball.h"
#include "render.h"

#include "goal.h"


#include <SDL2/SDL.h>


// initializes innovation
int ball::nextInnovation = 0;

// initializes vector of all balls
std::vector<std::reference_wrapper<ball>> ball::balls = {};

// current turn
int turn = 0;

// if the game is over
bool gameOver = false;




int main(int argc, char* argv[]) {

	int posX = 150, posY = 130, width = 1600, height = 800;

	// creates renderer, balls

	render Rendermain = render();

	ball Ballmain = ball(420.0f, 400.0f, SIX, WHITE, -300.f, -280.f);
	ball Ball2 = ball(1200.0f + Ballmain.Radius * 4, 400.0f, NONE, BLACK, 0, 0);

	// all orange balls
	ball Ball4 = ball(1200.0f, 400.0f, NONE, ORANGE, 0, 0);
	ball Ball5 = ball(1200.0f + Ball4.Radius * 2, 400.0f + Ball4.Radius, NONE, ORANGE, 0, 0);
	ball Ball6 = ball(1200.0f + Ball4.Radius * 8, 400.0f + Ball4.Radius * 4, NONE, ORANGE, 0, 0);
	ball Ball7 = ball(1200.0f + Ball4.Radius * 4, 400.0f - Ball4.Radius * 2, NONE, ORANGE, 0, 0);
	ball Ball8 = ball(1200.0f + Ball4.Radius * 6, 400.0f - Ball4.Radius * 3, NONE, ORANGE, 0, 0);
	ball Ball9 = ball(1200.0f + Ballmain.Radius * 8, 400.0f - Ball4.Radius * 2, NONE, ORANGE, 0, 0);
	ball Ball16 = ball(1200.0f + Ballmain.Radius * 6, 400.0f - Ball4.Radius, NONE, ORANGE, 0, 0);

	// all blue balls
	ball Ball10 = ball(1200.0f + Ball4.Radius * 4, 400.0f + Ball4.Radius * 2, NONE, BLUE, 0, 0);
	ball Ball11 = ball(1200.0f + Ball4.Radius * 6, 400.0f + Ball4.Radius * 3, NONE, BLUE, 0, 0);
	ball Ball12 = ball(1200.0f + Ball4.Radius * 2, 400.0f - Ball4.Radius, NONE, BLUE, 0, 0);
	ball Ball13 = ball(1200.0f + Ball4.Radius * 8, 400.0f - Ball4.Radius * 4, NONE, BLUE, 0, 0);
	ball Ball14 = ball(1200.0f + Ballmain.Radius * 8, 400.0f, NONE, BLUE, 0, 0);
	ball Ball15 = ball(1200.0f + Ballmain.Radius * 8, 400.0f + Ball4.Radius * 2, NONE, BLUE, 0, 0);
	ball Ball17 = ball(1200.0f + Ballmain.Radius * 6, 400.0f + Ball4.Radius, NONE, BLUE, 0, 0);

	// creates the goals
	goal Goal1 = goal(30, 30, 30);
	goal Goal2 = goal(30, height - 30, 30);


	goal Goal3 = goal(width - 30, height - 30, 30);
	goal Goal4 = goal(width - 30, 30, 30);


	goal Goal5 = goal(width / 2, height - 25, 25);
	goal Goal6 = goal(width / 2, 25, 25);


	// puts them in a vector
	std::vector<goal> Goals;
	Goals.push_back(Goal1);
	Goals.push_back(Goal2);
	Goals.push_back(Goal3);
	Goals.push_back(Goal4);
	Goals.push_back(Goal5);
	Goals.push_back(Goal6);




	// initializes SDL


	SDL_Window* win = NULL;
	SDL_Renderer* renderer = NULL;




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
		// adds one to turn
		turn++;

		// sets bg to pink
		SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);


		// clears screen
		SDL_RenderClear(renderer);

		// sets the boundaries
		std::vector<SDL_Rect> rects = Rendermain.setBoundary(renderer, width, height, Goal1);
		std::vector<SDL_Point> points = Rendermain.setBoundary2(renderer, Goals, rects);

		// if it should break out of the loop
		bool end = false;

		// moves every ball
		for (int i = 0; i < ball::balls.size(); i++) {
			ball& b = ball::balls[i];
			b.move(rects, width, Goal1, points);

			// draws each ball
			Rendermain.drawCircle(renderer, b, b.Radius, true);

			//goes through each goal and checks if a ball is in it
			for (goal& Goal : Goals) {
				// if > half of ball cross over goal, counts as goal
				if (Goal.isGoal(b.x, b.y, b.Radius)) {

					// if its the white ball that went in
					if (b.innovation == 1) {
						// puts the ball in the center
						b.x = 800;
						b.y = 400;

						// sets the velocity to 0
						b.velx = 0;
						b.vely = 0;

						// adds one to the turn as a penalty
						turn++;
						break;
					}
					// todo add the 7 balls going in if their of the right type and penalty for scoring the wrong type
					//   also if black ball goes into too early and if it goes in at the right time

					// erases the ball from the vector
					ball::balls.erase(ball::balls.begin() + i);

					// TODO: Add animation to make ball fade out
					std::cout << "Goal!" << std::endl;

					b.inGoal = true;

					end = true;
					break;
				}

			}

			// if it should break out of the loop early
			if (end) {
				break;
			}
		}

		for (goal& Goal : Goals) {
			Rendermain.drawGoal(renderer, Goal, true);
		}

		// presents screen
		SDL_RenderPresent(renderer);


		// sets framerate to 144 by delaying each frame if needed
		Uint32 frametime = SDL_GetTicks() - framestart;
		if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);
		// SDL_Delay(200);

	}




	return 0;
}
