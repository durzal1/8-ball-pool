#include <iostream>
#include "ball.cpp"
#include "render.cpp"
#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    ball Ballmain = ball(500, 500 , FIVE, 0, WHITE);
    render Rendermain = render();
    ball Ball2 = ball(700, 500, NONE, 0, SOLID);
    std::vector<ball> balls = {Ball2};

    Ball2.calculateCircumference();

    // initializes SDL

    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;

    int posX = 100, posY = 100, width = 900, height = 900;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    
    // SDL main event loop

    while (true) {
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

        Ballmain.move(balls);

        Ballmain.calculateCircumference();


        // draws circle
        SDL_RenderClear(renderer);
        Rendermain.drawCircle(renderer, Ball2);
        Rendermain.drawCircle(renderer, Ballmain);
        SDL_RenderPresent(renderer);

    }

    
    

    return 0;
}
