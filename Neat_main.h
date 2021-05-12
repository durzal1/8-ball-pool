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
#include "Prender.cpp"

// for kevin
//#include "ball.h"
//#include "render.h"

#include "POOL/goal.cpp"
#include "POOL/vector2f.h"
#include <SDL2/SDL.h>
#include "GetOutputs.h"
#include "Genome.h"
#include "POOL/types_.h"

// initializes innovation
int ball::nextInnovation = 0;

// initializes ballCollInno
int ball::ballCollInno = -1;

// initializes vector of all balls
std::vector<std::reference_wrapper<ball>> ball::balls = {};

double pool_main(Genome &genome) {
    // current turn
    int turn = 0;

    // if there is an infinite loop
    bool infiniteLoop = false;

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

    // if it should fix overlapping every frame
    bool fixOverlap = false;

    // vector of the balls it has correctly score
    std::vector<ball> correctScored;

    // vector of the balls it has incorrectly score
    std::vector<ball> incorrectScored;

    // current frame number
    int frameNum = 0;

    // turns the ball has gone without hitting another ball
    int turnsNoHit = 0;

    // at least one collision was made (per turn)
    bool collisionMade = false;

    // turns without scoring
    int turnsNoScore = 0;

    // the amount of balls in the balls scored vector last turn
    int ballsLastTurn = 0;

    int posX = 150, posY = 130, width = 1600, height = 800;

    // creates renderer, balls

    render Rendermain = render();


    ball Ballmain = ball(800.0f, 400.0f, THREE, WHITE, 690.f, 30.f);
    ball Ball2 = ball(1400, 600.0f, NONE, ORANGE, 0, 0);

    // all orange balls
    ball Ball4 = ball(200.0f, 200.0f, NONE, ORANGE, 0, 0);
    ball Ball5 = ball(600.0f , 200.0f, NONE, ORANGE, 0, 0);
    ball Ball6 = ball(1000.0f , 200.0f, NONE, ORANGE, 0, 0);
    ball Ball7 = ball(1400.0f , 200.0f , NONE, ORANGE, 0, 0);
    ball Ball8 = ball(200.0f , 600.0f , NONE, ORANGE, 0, 0);
    ball Ball9 = ball(600.0f , 600.0f, NONE, ORANGE, 0, 0);
    ball Ball16 = ball(1000.0f, 600.0f , NONE, ORANGE, 0, 0);


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

    // sets outputs (updated to set and not just give)
    getOutputs(Ballmain, Goals, genome, turn, blackBall);



    /// initializes SDL
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;




    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);



    Uint32 framestart;

    while (true) {
        framestart = SDL_GetTicks();
        frameNum ++;

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
        std::vector<SDL_Rect> rects = Rendermain.setBoundary(renderer,width, height, Goal1);
        std::vector<SDL_Point> points = Rendermain.setBoundary2( renderer, Goals, rects);

        // if it should break out of the loop
        bool end = false;

        // moves every ball
        for (int i = 0; i < ball::balls.size(); i++) {
            ball& b = ball::balls[i];

            // move func
            b.move(rects, width, Goal1, points, frameNum);

            // draws each ball
            Rendermain.drawCircle(renderer, b, b.Radius, true);

            //goes through each goal and checks if a ball is in it
            for (goal& Goal : Goals) {
                // if > half of ball cross over goal, counts as goal
                if (Goal.isGoal(b.x, b.y, b.Radius)) {

                    // if its the white ball that went in
                    if (b.innovation == 1) {
                        b.inGoal = true;
                        break;
                    }

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

                    b.inGoal = true;

                    end = true;

                    // adds the ball to the correct vector
                    correctScored.push_back(b);

                    // when there balls vector only has two elements black ball is ready to be scored
//                    if (ball::balls.size() == 2){
//                        blackBall = true;
//                    }

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

        for (ball &b:ball::balls){

            // if a collision happened
            if (b.hadCollision && b.BallType != WHITE && !b.isStuck){
                collisionMade = true;
            }

            // checks if the ball is stuck
            if (b.isStuck){
                b.velx = 0;
                b.vely = 0;
            }
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
                fixOverlap = true;

            }
        }

        // if it should fix overlapping
        if (fixOverlap){
            // checks for overlapping
            for (ball &b_ :Ballmain.balls){
                b_.fixOverlapping();
            }
        }

        // if all of the balls have stopped
        if (allStopped){
            // adds one to turn
            turn++;

            // if at least one collision was made it
            if (collisionMade){
                // resets turns without hit
                turnsNoHit = 0;

                // resets collisionMade
                collisionMade = false;
            }
            else{
                // no collision was made and it will add one to turns no hit
                turnsNoHit ++;
            }

            // makes every ball unstuck
            for (ball &b:ball::balls){
                b.isStuck = false;
                b.hadCollision = false;
            }

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
                turnsNoScore ++;

                Ballmain.inGoal = false;

            }

            // checks if a ball was scored this turn
            if (correctScored.size() > ballsLastTurn){
                // a ball was scored

                // updates the ballsLastTurn variable
                ballsLastTurn= correctScored.size();

                // resets turnsNoScore
                turnsNoScore = 0;
            }
            else{
                // a ball was not scored

                // adds one to turnsNoScore
                turnsNoScore ++;

                // sets ballsLastTurn
                ballsLastTurn = correctScored.size();


            }

            // sets outputs (updated to set and not just give)
            getOutputs(Ballmain, Goals, genome, turn, blackBall);



        }

        // if there is over 4 turns without a hit it will end the game
        // OR if it has been 10 or over turns since ball was scored
        if (turnsNoHit > 5 || turnsNoScore >= 20 || turn >= 100){
            gameOver = true;
            infiniteLoop = true;
        }

        // presents screen
        SDL_RenderPresent(renderer);

        // sets framerate to 144 by delaying each frame if needed
        Uint32 frametime = SDL_GetTicks() - framestart;

        if (1000 / 144 > frametime) SDL_Delay(1000 / 144 - frametime);
        SDL_Delay(0);


        // if the game is over
        if (gameOver){
            /// fitness function


            // sets fit to 10 to make sure fitness doesnt go negative
            double fitness = 20;

            // decreases 8 if ball was in an infinite loop
            if (turnsNoHit > 2){
                fitness -= 8;
            }
            // decreases 10 if black ball is scored too early
            else if (gameOver && !WIN){
                fitness -= 10;
            }
            // computer won
            else{
                // adds 15 to fitness
                fitness += 15;
            }

            // adds max 2 if the turn is over 200
            if (turn > 30){
                fitness += 2;
            }
            // if its less than 200 it will add the turn / 200
            else{
                fitness += (turn * 1.0 / 30);
            }

            // decreases 1 per wrong ball scored
            fitness -= incorrectScored.size();

            // adds 2 per correct ball scored
            fitness += 2 * (correctScored.size());



            // resets some ball attributes
            ball::nextInnovation = 0;
            ball::balls.clear();

            /// EXPIREMENTAL FITNESS BASED OFF THE ONE I USED FOR SNAKE
            // how the program lost 0 = infinite loop, 1 = black ball first
            int howLost = -1;

            // var to lessen fitness
            double Penalty = 0;

            // if game over was caused by an infinite loop
            if (infiniteLoop){
                // gives a penalty of 0.5
                Penalty = 0.5;
                howLost = 0;
            }
            else if (gameOver && !WIN){
                // black ball was scored too early

                // gives penalty of 0.75
                Penalty = 0.55;

                howLost = 1;
            }
            else{
                // player won and gives infinite score
                Penalty = 999999999;
            }

            double secondPart = (pow(2, correctScored.size()) + pow(correctScored.size(), 2.1) *500);
            double lastPart = (pow(correctScored.size(), 1.2) * pow((0.25 * turn), 1.3) * 25);
            double fitness2 = (3 * turn + secondPart - lastPart) * Penalty;

            // resets the fitness of the genome
            genome.fitness = fitness2;

            // adds some other attributes useful for testing
            genome.rightScored = correctScored.size();
            genome.turnsPool = turn;
            genome.howLost = howLost;


            /// todo DEF ADD if dying from black ball becomes a big issue add the direction to the black ball as an input
            // todo also try only allowed 20-25 turns max
            return fitness2;
        }
    }




}

#endif //POOL_NEAT_MAIN_H
