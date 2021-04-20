#include "render.h"

// draws circle
int render::drawCircle(SDL_Renderer* renderer, ball ball, int radius, bool fill)
{
    int r = ball.getColor().r;
    int g = ball.getColor().g;
    int b = ball.getColor().b;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    int offsetx, offsety, d;
    int status;


    SDL_Point p = ball.getPixels();
    int x = p.x;
    int y = p.y;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {

            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    if (fill) {


        offsetx = 0;
        offsety = radius;
        d = radius - 1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }



    return status;

}

// draws goal
int render::drawGoal(SDL_Renderer *renderer,  goal Goal, bool fill) {

    int r = 255;
    int g = 0;
    int b = 0;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    int offsetx, offsety, d;
    int status;

    SDL_Point p = Goal.getPixels();
    int x = p.x;
    int y = p.y;

    int radius = Goal.Radius;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {

            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    if (fill) {


        offsetx = 0;
        offsety = radius;
        d = radius - 1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                         x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                         x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                         x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                         x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }



    return status;

}
// sets the extra boundaries
std::vector<SDL_Rect> render::setBoundary(SDL_Renderer *renderer, int WIDTH, int HEIGHT, goal Goal) {
    // sets variables
    int leastx = 50, leasty = 50, mostx = int(WIDTH - Goal.Radius * 1.5), mosty = int(HEIGHT - Goal.Radius * 1.5);

    // creates the rectangles to represent the borders
    SDL_Rect r1{0, int(Goal.Radius * 2.8), int(Goal.Radius * 1.5), int(HEIGHT - (Goal.Radius * 5.6))};
    SDL_Rect r6{mostx, int(Goal.Radius * 2.8), int(Goal.Radius * 1.5), int(HEIGHT - (Goal.Radius * 5.6))};

    SDL_Rect r2{int(Goal.Radius * 2.8), 0, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};
    SDL_Rect r3{int(Goal.Radius * 2.8), mosty, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};

    SDL_Rect r4{WIDTH / 2 + int(Goal.Radius * 1.8) , mosty, int(HEIGHT - (Goal.Radius * 4.7)), int(Goal.Radius * 1.5)};
    SDL_Rect r5{WIDTH / 2 + int(Goal.Radius * 1.8), 0, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};

    //todo add real boundaries

    // sets the render color to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // renders the rectangles
    SDL_RenderFillRect(renderer, &r1);
    SDL_RenderFillRect(renderer, &r2);
    SDL_RenderFillRect(renderer, &r3);
    SDL_RenderFillRect(renderer, &r4);
    SDL_RenderFillRect(renderer, &r5);
    SDL_RenderFillRect(renderer, &r6);

    // adds rectangles into a vector
    std::vector<SDL_Rect> rects;
    rects.push_back(r1);
    rects.push_back(r2);
    rects.push_back(r3);
    rects.push_back(r4);
    rects.push_back(r5);
    rects.push_back(r6);

    return rects;
}
//