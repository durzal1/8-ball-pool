#include <iostream>
// for zacky
 #include "ball.cpp"
 #include "render.cpp"

// for kevin
//#include "ball.h"
//#include "render.h"


#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    ball Ballmain = ball(500, 500, FIVE, 300, SOLID, 0);
    render Rendermain = render();
    ball Ball2 = ball(700, 650, NONE, 0, SOLID, 1);

    std::vector<ball> balls = { Ball2 };
       
    
    

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



        // moves the balls

        // removes one from the velocity
        Ballmain.velocity -= 1;

        for (int i = 0; i < Ballmain.velocity; i ++) {
            // sets bg to pink
            SDL_SetRenderDrawColor(renderer, 255, 23, 255, 0);

            SDL_RenderClear(renderer);

            // moves the main ball
            Ballmain.move(balls);

            // goes through each ball to see if one their velocities is over 0
            for (ball& Ball:balls){
                if (Ball.velocity > 0){
                    // moves the ball
                    Ball.move(balls);
                }
                Rendermain.drawCircle(renderer, Ball, 30, true);
            }
            // draws circles
            Rendermain.drawCircle(renderer, Ballmain, 30, true);


            SDL_RenderPresent(renderer);
        }
       



    }




    return 0;
}
