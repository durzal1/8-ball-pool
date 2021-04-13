#include <iostream>
#include "ball.h"
#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    ball Ballmain = ball(500, 500 , ONE, 30, WHITE);

    ball Ball2 = ball(600, 500 , NONE, 0, SOLID);

    std::vector<ball> balls = {Ball2};
    Ballmain.move(balls);
    return 0;
}
