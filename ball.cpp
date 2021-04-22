//
// Created by zacky on 4/12/2021.
//

#include "ball.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include <SDL2/SDL.h>
#include "goal.h"


// Radius for movement (should always be one)
int MoveRad = 1;

// x and y max constant in pixels
int XMAX = 1600;
int YMAX = 800;

// for fixed FPS
int frametime;
const int FPS = 144;
const int delay = 1000 / FPS;


float friction = 0.8f;
float stopBall = 3.2f;

// constructor
ball::ball(Pixel x, Pixel y, power p, ballType Balltype, float velx, float vely) {
    this->x = x;
    this->y = y;
    this->velx = velx * p;
    this->vely = vely * p;
    this->initialPower = p;
    this->BallType = Balltype;
    this->innovation = innovation;
    this->mass = Radius * 5.0f;
    this->ax = 0;
    this->ay = 0;
    this->innovation = 0;

    // updates innovation
    this->innovation = ++nextInnovation;

    // updates vector of balls
    this->balls.push_back(*this);
}

//moving function
void ball::move(std::vector<SDL_Rect> rects, int HEIGHT, goal Goal, std::vector<SDL_Point> points) {
    // calculates friction
    this->ax = -this->velx * friction;
    this->ay = -this->vely * friction;


    // calculates vels
    float timeDelta = 1.0f / FPS;


    velx += this->ax * timeDelta;
    vely += this->ay * timeDelta;


    // puts ball to a stop after slowing down certain amount
    if (fabs(this->velx * this->velx + this->vely * this->vely) < stopBall) {
        this->velx = 0, this->vely = 0;
    }


    // calculates x, y
    this->x += this->velx * timeDelta;
    this->y += this->vely * timeDelta;

    
    // wall collision
    if (checkForCollisionWall(rects, HEIGHT, Goal, points)) collisionWall();

    // ball collision
    for (ball& b : balls) {
        // makes sure it isnt detecting same ball
        if (b.innovation != this->innovation) {
            if (checkForCollisionBall(b)) {
                collisionBall(b);
            }
        }
    }


}

//function that will check if a collision has occurred with another ball
bool ball::checkForCollisionBall(ball& ball_) {

    return fabs(powf(this->x - ball_.x, 2) + powf(this->y - ball_.y, 2)) <= pow(Radius * 2, 2);

}
//
// function that will check if a collision has occurred with the wall
bool ball::checkForCollisionWall(std::vector<SDL_Rect> rects, int WIDTH, goal Goal, std::vector<SDL_Point> points) {
    FrameSinceLast ++;
    if (innovation != 1){
        return false; //todo REMOVE
    }
    /// checks with the primary boundary


    for (SDL_Rect rect:rects){

        // left and right
        if (rect.x == 0){
            if (x - Radius<= rect.w + rect.x && y > rect.y && y < rect.y + rect.h){
                count_left ++;

                if (count_left == 1){
                    ColWall = LEFT;
                    WierdAngle = true;
                    goLeft = false;
                    return true;
                }

                if (goLeft){
                    ColWall = LEFT;
                    return true;
                }
            }

        }
        else if( rect.x == int(WIDTH - Goal.Radius * 1.5)){
            if (  ( (x + Radius >= rect.x) && (x + Radius <= rect.w + rect.x)  ) && y > rect.y && y < rect.y + rect.h){
                if (!WierdAngle){
                    ColWall = RIGHT;
                    WierdAngle = true;
                    goRight = false;
                    return true;
                }
                if (goRight){
                    ColWall = RIGHT;
                    return true;
                }
            }

        }

        // middle

        // if its in the wall
        else if( ( ( (x + Radius >= rect.x) && (x <= rect.w+ rect.x) ) || ( (x >= rect.x) && (x - Radius<= rect.w+ rect.x) )) &&  ( (y + Radius >= rect.y  &&  y +Radius <= rect.h+ rect.y) || (y - Radius <= rect.y  &&  y - Radius >= rect.h+ rect.y)  ) ){

             if (!WierdAngle){
                ColWall = DOWN;
                WierdAngle = true;
                goUpDown = false;
                return true;
            }
            if (goUpDown){
                 ColWall = DOWN;
                 return true;
            }
        }
        else if ((x >= rect.x) && x - Radius<= rect.w+ rect.x && (y - Radius >= rect.y  &&  y - Radius <= rect.h+ rect.y)){
            if (!WierdAngle){
                ColWall = DOWN;
                WierdAngle = true;
                return true;
            }
            if (goUpDown){
                ColWall = DOWN;
                return true;
            }
        }


    }
    if (FrameSinceLast < 3){
        return false;
    }
    /// checks with the secondary boundary
    for (int i = 0; i < points.size(); i ++){
        // makes sure it is the first point of the line
        if (i % 2 != 0){
            continue;
        }


        SDL_Point point1 = points[i];
        SDL_Point point2 = points[i+1];



        // top left
        if ( point2.x < x && x < point1.x && point2.y < y  && y< point1.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        else if (point1.x < x && x < point2.x && point1.y < y && y  < point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }

        // bottom left
        else if ( point2.x < x && x < point1.x && point2.y > y  && y> point1.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        else if (point1.x < x && x < point2.x && point1.y > y && y > point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        //todo add goal collisions
        // 2 main issues rn
        // 1) the slanted collisions are only accurate 50% time where you would need to change the x and y
        // the other 50% where you only need to change one arent accurate
        // the only way to solve this is to make a function that can find which one it is
        // 2) its possible that it might get stuck in the walls sometimes too

        // top right
        else if ( point1.x  > x  && x   > point2.x && point1.y < y   && y  < point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        else if (point1.x < x && x < point2.x && point1.y > y && y  > point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }

        // bottom right
        else if ( point1.x  > x  && x   > point2.x && point1.y < y   && y  < point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        else if (point1.x < x && x < point2.x && point1.y > y && y  > point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }

        // mid top
        else if ( point1.x < x && x - 7 < point2.x && point1.y > y  && y  > point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }
        else if (point1.x < x && x < point2.x && point1.y > y && y  > point2.y){
            velx = -velx;
            vely = -vely;
            FrameSinceLast = 0;
            return false;
        }



    }

    return false;
}

// function that will happen if a collision occurred with a wall
void ball::collisionWall() {
    if (ColWall == LEFT || ColWall == RIGHT) velx = -velx;
    else if (ColWall == UP || ColWall || DOWN) vely = -vely;
}

// function that will happen if a collision occurred with a ball
void ball::collisionBall(ball& ball1) {
    // distance between balls
    float dist = sqrtf(powf(this->x - ball1.x, 2) + powf(this->y - ball1.y, 2));

    // Normal
    float nx = (ball1.x - this->x) / dist;
    float ny = (ball1.y - this->y) / dist;

    // Tangent
    float tx = -ny;
    float ty = nx;

    // dot prod tan
    float dpTan1 = this->velx * tx + this->vely * ty;
    float dpTan2 = ball1.velx * tx + ball1.vely * ty;

    // dot prod norm
    float dpNorm1 = this->velx * nx + this->vely * ny;
    float dpNorm2 = ball1.velx * nx + ball1.vely * ny;

    // conservation of mass
    float m1 = (dpNorm1 * (this->mass - ball1.mass) + 2.0f * ball1.mass * dpNorm2) / (this->mass + ball1.mass);
    float m2 = (dpNorm2 * (ball1.mass - this->mass) + 2.0f * this->mass * dpNorm1) / (this->mass + ball1.mass);
    
    // adds to velocities
    this->velx = tx * dpTan1 + nx * m1;
    this->vely = ty * dpTan1 + ny * m1;
    ball1.velx = tx * dpTan2 + nx * m2;
    ball1.vely = ty * dpTan2 + ny * m2;

}



// returns point
SDL_Point ball::getPixels() {
    return SDL_Point({ (int)this->x, (int)this->y });
}


// returns color
SDL_Color ball::getColor() {
    SDL_Color color = {};



    switch (this->BallType)
    {
    case SOLID:
        color = { 20, 39, 255 }; //  blue for now
        break;
    case BLACK:
        color = { 0, 0, 0 };
        break;
    case STRIPE:
        color = { 255, 165, 0 }; // orange for now
        break;
    case WHITE:
        color = { 255, 255, 255 };
    default:
        break;
    }

    return color;
}
