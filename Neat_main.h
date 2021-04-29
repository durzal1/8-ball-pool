//
// Created by zacky on 4/29/2021.
//

#ifndef POOL_NEAT_MAIN_H
#define POOL_NEAT_MAIN_H

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
#include "GetOutputs.h"

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
double pool_main(int argc, char* argv[]) {

    int posX = 150, posY = 130, width = 1600, height = 800;

    // creates renderer, balls

    render Rendermain = render();


    ball Ballmain = ball(400.0f, 400.0f, SIX, WHITE, 690.f, -30.f);
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

    // gets outputs
    std::vector<double> outputs = geOutputs(Ballmain, Goals);







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

            // if one of the balls have come to a complete stop
            if (b.velx == 0 && b.vely == 0 && b.hadCollision ){
                // checks for overlapping
                for (ball &b_ :b.balls){
                    b_.fixOverlapping();
                }

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

            /// fitness function

            // sets fit to 10 to make sure fitness doesnt go negative
            double fitness = 10;

            // decreases 4 if black ball is scored too early
            if (gameOver && !WIN){
                fitness -= 4;
            }

            // decreases 1 per wrong ball scored
            fitness -= incorrectScored.size();

            // adds 2 per correct ball scored
            fitness += correctScored.size();

        }
        // presents screen
        SDL_RenderPresent(renderer);


        // sets framerate to 144 by delaying each frame if needed
        Uint32 frametime = SDL_GetTicks() - framestart;
        if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);

    }




    return 0;
}

#endif //POOL_NEAT_MAIN_H
