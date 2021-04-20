#include <iostream>
#include <functional>
// for zacky
 #include "ball.cpp"
 #include "render.cpp"

// for kevin
//#include "ball.h"
//#include "render.h"

#include "goal.h"


#include <SDL2/SDL.h>


// initializes innovation
int ball::nextInnovation = 0;

// initializes vector of all balls
std::vector<std::reference_wrapper<ball>> ball::balls = {};

int main(int argc, char* argv[]) {

    int posX = 150, posY =130, width = 1600, height = 800;

    // creates renderer, balls

	render Rendermain = render();
	ball Ballmain = ball(500.0f, 60.0f, FIVE, SOLID, -500, 300);
	ball Ball2 = ball(730.0f, 300.0f, NONE, SOLID, 0, 0);
	ball Ball3 = ball(850.0f, 200.0f, NONE, BLACK, 0, 0);

	// creates the goals
	goal Goal1 = goal(30, 30, 30);
	goal Goal2 = goal(30, height - 30, 30);


	goal Goal3 = goal(width - 30, height - 30, 30);
	goal Goal4 = goal(width - 30, 30, 30);


	goal Goal5 = goal(width / 2, height - 25, 25);
	goal Goal6 = goal(width / 2 , 25, 25);


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

        // sets bg to pink
        SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);


        // clears screen
        SDL_RenderClear(renderer);

        // sets the boundary
        std::vector<SDL_Rect> rects = Rendermain.setBoundary(renderer, width, height, Goal1);


        // moves every ball
		for (ball& b : ball::balls){
            b.move(rects, width, Goal1);

            // draws each ball
            Rendermain.drawCircle(renderer, b, b.Radius, true);

            //goes through each goal and checks if a ball is in it
            for (goal& Goal:Goals){
//                float dist = fabs(powf(b.x - (Goal.x + Goal.WIDTH / 2), 2) + powf(b.y - (Goal.y + 50), 2));

                // if ball is in the goal
//                if (dist <= 500) {
//                    SDL_Delay(0);
//                }
            }

        }

        for (goal& Goal:Goals){
            Rendermain.drawGoal(renderer, Goal, true);
        }

        // presents screen
        SDL_RenderPresent(renderer);


        // sets framerate to 144 by delaying each frame if needed
		Uint32 frametime = SDL_GetTicks() - framestart;
		if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);

	    SDL_Delay(50);
	}




	return 0;
}
