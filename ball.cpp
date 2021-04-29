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

    // if the ball's velocity is 0 it wont go through this loop
    if (velx != 0 || vely != 0){
        // ball collision
        for (ball& b : balls) {
            // makes sure it isnt detecting same ball
            if (b.innovation != this->innovation) {
                if (checkForCollisionBall(b)) {
                    collisionBall(b);
                }
            }
        }

        // calculates friction
        this->ax = -this->velx * friction;
        this->ay = -this->vely * friction;

        // calculates vels
        float timeDelta = 1.0f / FPS;


        velx += this->ax * timeDelta;
        vely += this->ay * timeDelta;


        // puts ball to a stop after slowing down certain amount
        float speed = fabs(this->velx * this->velx + this->vely * this->vely);
        if ( speed < stopBall) {
            this->velx = 0, this->vely = 0;
        }


        // calculates x, y
        this->x += this->velx * timeDelta;
        this->y += this->vely * timeDelta;


        // wall collision
        collisionAllWalls(rects, HEIGHT, Goal, points);

        // checks if its velocity is not 0
        if (velx != 0 && vely !=0){
            hadCollision = true;
        }
    }





}
// function to check if there are any balls that remain overlapping and fix them
void ball::fixOverlapping(){
    // goes through every ball
    for (ball& b : balls) {
        // makes sure it isnt detecting same ball
        if (b.innovation != this->innovation) {
            int l = fabs(powf(this->x - b.x, 2) + powf(this->y - b.y, 2));
            // balls are in each other
            if (l <= 1550){
                // distance between balls
                float dist = sqrtf(powf(this->x - b.x, 2) + powf(this->y - b.y, 2));

                // displace so they do not get stuck
                float displace = 1.0f * (dist - Radius - 1);

                x -= displace * ( b.x - x ) / dist;
                y -= displace * (b.y - y) / dist;
            }
        }
    }
}
//function that will check if a collision has occurred with another ball
bool ball::checkForCollisionBall(ball& ball_) {
    int f = pow(Radius * 2, 2) ;
    int l = fabs(powf(this->x - ball_.x, 2) + powf(this->y - ball_.y, 2));

    // balls are in each other
    if (l <= 800){
        // distance between balls
        float dist = sqrtf(powf(this->x - ball_.x, 2) + powf(this->y - ball_.y, 2));

        // displace so they do not get stuck
        float displace = 1.0f * (dist - Radius - 1);

        int x_ =  displace * ( ball_.x - x ) / dist;
        int y_ = displace * (ball_.y - y) / dist;
        x -= displace * ( ball_.x - x ) / dist;
        y -= displace * (ball_.y - y) / dist;
    }
    // if its just a regular collision
    else if (l <= f){
        return true;
    }
    return false;

}

// function that will handle wall collision
bool ball::collisionAllWalls(std::vector<SDL_Rect> rects, int WIDTH, goal Goal, std::vector<SDL_Point> points) {


	/// checks with all walls and lines
	for (int i = 0; i < points.size(); i++) {
		// makes sure it is the first point of the line
		if (i % 2 != 0) {
			continue;
		}

		// two points
		SDL_Point p1 = points[i];
		SDL_Point p2 = points[i + 1];


		float line1x = p1.x - p2.x;
		float line1y = p1.y - p2.y;


		float line2x = x - p2.x;
		float line2y = y - p2.y;

		// length of line segment
		float len = line1x * line1x + line1y * line1y;

		// clamped value between 0 and 1
		float d = std::fmax(0, fmin(len, line1x * line2x + line1y * line2y)) / len;


		// closest x, y value on segment
		float closeX = p2.x + d * line1x;
		float closeY = p2.y + d * line1y;

		// ditance between ball and closest x, y on segment
		float dist = sqrtf((x - closeX) * (x - closeX) + (y - closeY) * (y - closeY));

		// if they touch...
		if (dist <= Radius) {


			// displace so they do not get stuck
			float displace = 1.0f * (dist - Radius - 1);


			x -= displace * (x - closeX) / dist;
			y -= displace * (y - closeY) / dist;

			// distance between objects
			float dist2 = sqrtf(powf(this->x - closeX, 2) + powf(this->y - closeY, 2));

			// Normal
			float nx = (closeX - this->x) / dist2;
			float ny = (closeY- this->y) / dist2;

			// Tangent
			float tx = -ny;
			float ty = nx;

			// dot prod tan
			float dpTan1 = this->velx * tx + this->vely * ty;
			float dpTan2 = (-velx * tx) + (-vely * ty);

			// dot prod norm
			float dpNorm1 = this->velx * nx + this->vely * ny;
			float dpNorm2 = (-velx * nx) + (-vely * ny);

			// conservation of mass
			float massWall = this->mass * 0.7f;
			float m1 = (dpNorm1 * (this->mass - massWall) + 2.0f * (massWall) * dpNorm2) / (this->mass + (massWall));
			float m2 = (dpNorm2 * (massWall - this->mass) + 2.0f * this->mass * dpNorm1) / (this->mass + (massWall));

			// adds to velocities
			this->velx = tx * dpTan1 + nx * m1;
			this->vely = ty * dpTan1 + ny * m1;

		}
	}

	return false;
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
	    case WHITE:
            color = { 255, 255, 255 };
            break;
	case BLUE:
		color = { 20, 39, 255 }; //  blue for now
		break;
	case BLACK:
		color = { 0, 0, 0 };
		break;
	case ORANGE:
		color = { 255, 165, 0 }; // orange for now
		break;
		case GREEN:
        color = {0, 255, 0};
        break;
	default:
		break;
	}

	return color;
}
