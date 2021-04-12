#include <iostream>
#include "ball.cpp"
#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    ball Ball = ball(500, 500 , ONE, 30, SOLID);
    Ball.move();
    return 0;
}
