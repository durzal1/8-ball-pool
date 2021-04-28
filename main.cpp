#include <iostream>
#include <functional>
#include <vector>
#include "algorithm"


// for zacky
#include "ball.cpp"
#include "render.cpp"

// for kevin
//#include "ball.h"
//#include "render.h"

#include "goal.h"
#include "vector2f.h"
#include <SDL2/SDL.h>


// initializes innovation
int ball::nextInnovation = 0;

// initializes vector of all balls
std::vector<std::reference_wrapper<ball>> ball::balls = {};

// current turn
int turn = 0;

// if the game is over
bool gameOver = false;

// error margin
const float errorMargin = 0.1;

// the ball computer should aim for
const ballType winCondition = ORANGE;

// if computer won
bool WIN = false;

// if the ball is ready to get the black ball
bool blackBall = false;

// vector of the balls it has correctly score
std::vector<ball> correctScored;

// vector of the balls it has incorrectly score
std::vector<ball> incorrectScored;
int main(int argc, char* argv[]) {

	int posX = 150, posY = 130, width = 1600, height = 800;

	// creates renderer, balls

	render Rendermain = render();


	// TODO: fix balls when glitching in each other
	ball Ballmain = ball(400.0f, 400.0f, SIX, WHITE, 620.f, -280.f);
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


    //// sets the new power and velocity
    //// gets the inputs

    /// finds the closest ball

    // vector of distances
    std::vector<float> distances;

    // loops through each ball and finds the distance between it and white ball
    for (ball &b:ball::balls){
        // if its the white ball it goes next
        if (b.innovation == 1) continue;

        // distance formula
        double dist = sqrt( pow((b.x - Ballmain.x), 2) + pow((b.y - Ballmain.y), 2) );

        // adds the dist to distances vector
        distances.push_back(dist);
    }


    // finds the lowest distance
    auto distMin = (*min_element(distances.begin(), distances.end()));

    // gets the index
    auto it = std::find(distances.begin(), distances.end(), distMin);
    int index = it- distances.begin();

    // sets the closet ball
    ball closestBall = Ballmain.balls[index + 1];

    // distance optamized to work with neat
    double distMinOpt = (distMin / 10) / 178;
    double distMinOpt2 = pow(0.9, distMin / 10);



    // finds the angle between the white ball and closest ball

    float delta_x = (closestBall.x) - Ballmain.x;
    float delta_y =(closestBall.y) - Ballmain.x;

    // angle in radians
    double thetaRadiansBall = atan2(delta_y, delta_x);


    /// finds the closest goal to closest ball

    // vector of distances
    std::vector<float> distancesGoals;

    for (goal g:Goals){
        // distance formula
        double dist = sqrt( pow((g.x - closestBall.x), 2) + pow((g.y - closestBall.y), 2) );

        // adds the dist to distances vector
        distancesGoals.push_back(dist);
    }

    // finds the lowest distance
    auto distMinGoal = (*min_element(distancesGoals.begin(), distancesGoals.end()));

    // gets the index
    auto it1 = std::find(distancesGoals.begin(), distancesGoals.end(), distMinGoal);
    int index1 = it1- distancesGoals.begin();

    // sets the closet ball
    goal closestGoal = Goals[index1];

    // distance optamized to work with neat
    double distMinOptGoal = (distMinGoal / 10) / 178;
    double distMinOpt2Goal = pow(0.9, distMinGoal / 10);


    // angle between closest ball and its closest goal

    float delta_x2 = (closestGoal.x) - closestBall.x;
    float delta_y2 =(closestGoal.y) - closestBall.x;

    // angle in radians
    double thetaRadiansGoal = atan2(delta_y2, delta_x2);


    // vector of all inputs
    std::vector<double> inputs {distMinOpt2, thetaRadiansBall, distMinOpt2Goal, thetaRadiansGoal};

    std::cout << "F";

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

		// sets the boundaries
		std::vector<SDL_Rect> rects = Rendermain.setBoundary(renderer, width, height, Goal1);
		std::vector<SDL_Point> points = Rendermain.setBoundary2(renderer, Goals, rects);

		// if it should break out of the loop
		bool end = false;

		// moves every ball
		for (int i = 0; i < ball::balls.size(); i++) {
			ball& b = ball::balls[i];

            // move func
            b.move(rects, width, Goal1, points);

            // draws each ball
            Rendermain.drawCircle(renderer, b, b.Radius, true);
			//goes through each goal and checks if a ball is in it
			for (goal& Goal : Goals) {
				// if > half of ball cross over goal, counts as goal
				if (Goal.isGoal(b.x, b.y, b.Radius)) {

					// if its the white ball that went in
					if (b.innovation == 1) {

					    b.inGoal = true;
						// adds one to the turn as a penalty
						turn++;
						break;
					}
					//todo   at the end it will penalize based off of the length of the incorrect ball vector
					//   when blackBall is true change the input to target black ball
					//  make get output a function

					if (b.BallType == BLACK){
					    switch (blackBall){
                            // if it got black ball in at the right time
                            case true:
					            // game is over and computer won
					            gameOver = true;
					            WIN = true;
                                break;
					        case false:
					            // game is over and computer lost
					            gameOver = true;
                                break;

					    }
					}
					// erases the ball from the vector
					ball::balls.erase(ball::balls.begin() + i);

					std::cout << "Goal!" << std::endl;

					b.inGoal = true;

					end = true;

					// checks if the ball is the right type
					switch (b.BallType == winCondition){
					    // if it is correct
					    case true:
                            // adds the ball to the correct vector
                            correctScored.push_back(b);
                            break;

					    // if it is not the right type
					    case false:
					        // adds the ball to the incorrect vector
					        incorrectScored.push_back(b);
					        break;
					}

					// checks if the correct ball vector has 7 balls in it
					switch (incorrectScored.size() == 7){
					    // if it has 7
					    case true:
					        // computer is ready to score black ball
					        blackBall = true;
                            break;
					}
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
		bool allStopped = true;
        for (ball b:ball::balls){
            float speed = fabs(b.velx * b.velx + b.vely * b.vely);

            // makes sure the velx and vely are not already 0
            if (b.velx != 0 || b.vely !=0){
                // rounds down if its within error margin
                if (errorMargin > speed){
                    b.velx = 0, b.vely = 0;
                }
            }

            // if one of them is still moving it will make allStopped false
            if (b.velx != 0 || b.vely != 0){
                allStopped = false;
            }
        }
        // if all of the balls have stopped
        if (allStopped){
            // adds one to turn
            turn++;

            // if the white ball is in the goal
            if (Ballmain.inGoal){
                // puts the ball in the center
                Ballmain.x = 800;
                Ballmain.y = 400;

                // sets the velocity to 0
                Ballmain.velx = 0;
                Ballmain.vely = 0;

                // adds an extra one to turn as penalty
                turn ++;

                allStopped = false;
            }
            for (ball b:ball::balls){
                // resets every ball
                b.inGoal = false;
            }
            //// sets the new power and velocity

            /// gets the inputs

            // finds the closest ball

            // vector of distances
            std::vector<float> distances;

            // loops through each ball and finds the distance between it and white ball
            for (ball &b:ball::balls){
                // if its the white ball it goes next
                if (b.innovation == 1) continue;

                // distance formula
                double dist = sqrt( pow((b.x - Ballmain.x), 2) + pow((b.y - Ballmain.y), 2) );

                // adds the dist to distances vector
                distances.push_back(dist);
            }
            // finds the lowest distance
            auto distMin = *min_element(distances.begin(), distances.end());

            // gets the index
            auto it = std::find(distances.begin(), distances.end(), distMin);
            int index = it- distances.begin();

            // sets the closet ball
            ball closestBall = Ballmain.balls[index];

            // distance optamized to work with neat
            double distMinOpt = pow(distMin, 0.1);
            std::cout << "F";
        }
		// presents screen
		SDL_RenderPresent(renderer);


		// sets framerate to 144 by delaying each frame if needed
		Uint32 frametime = SDL_GetTicks() - framestart;
		if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);

	}




	return 0;
}
