//
// Created by zacky on 4/29/2021.
//

#ifndef POOL_GETINPUTS_H
#define POOL_GETINPUTS_H

#include "ball.h"
#include "goal.h"
#include "render.h"
//// gets the inputs
void getOutputs(ball &Ballmain, std::vector<goal> Goals, int turn, bool scoreBlack, render &Rendermain, std::vector<ball> balls){
    /// finds the closest ball

    // if its found a good target
    bool goodTarget = false;

    while (!goodTarget){
        // vector of distances
        std::vector<float> distances;

        // sets the closet ball
        ball closestBall = Ballmain;

        // innovation that will delete a ball if its not optimal
        int inno;

        int index;
        double distMin;

        if (balls.size() == 2 && !scoreBlack){
            // if all the balls werent optimal

            // chooses the first ball to target
            closestBall = Ballmain.balls[2];

            // gets the distance
            distMin = sqrt( pow((closestBall.x - Ballmain.x), 2) + pow((closestBall.y - Ballmain.y), 2) );

        }
        else{
            // loops through each ball and finds the distance between it and white ball
            for (ball &b:balls){

                // if its the white ball it goes next
                if (b.innovation == 1) continue;

                // if scoreBlack is false and its a black ball
                if (!scoreBlack && b.innovation == 2) continue;

                // distance formula
                float dist = sqrt( pow((b.x - Ballmain.x), 2) + pow((b.y - Ballmain.y), 2) );

                // adds the dist to distances vector
                distances.push_back(dist);
            }


            // finds the lowest distance
            distMin = (*min_element(distances.begin(), distances.end()));

            // gets the index
            auto it = std::find(distances.begin(), distances.end(), distMin);
            index = it- distances.begin();

            if (scoreBlack){
                // includes black ball
                closestBall = balls[1];
                inno = 1;
                distMin = sqrt( pow((balls[1].x - Ballmain.x), 2) + pow((balls[1].y - Ballmain.y), 2) );
            }
            else{
                // does not include black ball
                closestBall = balls[index + 2];
                inno = index + 2;
            }

        }





        // distance optamized to work with neat
        float distMinOpt = (distMin / 10) / 178;
        float distMinOpt2 = pow(0.9, distMin / 10);

        // finds the angle between the white ball and closest ball

        float delta_x = (closestBall.x) - Ballmain.x;
        float delta_y =(closestBall.y) - Ballmain.x;

        // angle in radians
        float thetaRadiansBall = atan2(delta_y, delta_x);

        int speed = 1;

        double distanceX = closestBall.x - Ballmain.x;
        double distanceY = closestBall.y - Ballmain.y;
        double distance_direct = sqrt((distanceX * distanceX) + (distanceY * distanceY)); // pythagoras

        float vectorX = distanceX * (speed / distance_direct);
        float vectorY = distanceY * (speed / distance_direct);

/// finds the closest goal to closest ball

        // vector of distances
        std::vector<float> distancesGoals;

        for (goal g:Goals){
            // distance formula
            float dist = sqrt( pow((g.x - closestBall.x), 2) + pow((g.y - closestBall.y), 2) );

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
        float distMinOptGoal = (distMinGoal / 10) / 178;
        float distMinOpt2Goal = pow(0.9, distMinGoal / 10);


        // angle between closest ball and its closest goal

        float delta_x2 = (closestGoal.x) - closestBall.x;
        float delta_y2 =(closestGoal.y) - closestBall.x;

        // angle in radians
        float thetaRadiansGoal = atan2(delta_y2, delta_x2);

        /// new formula i made



        // sets some variables

        int x1 = closestBall.x;
        int y1 = closestBall.y;

        int x2 = closestGoal.x;
        int y2 = closestGoal.y;

        // exceptions if the line is vertical / horizontal

        if (x2 - x1 == 0){
            // vertical line

            // sets velx to 0
            double setVelx = 0;
            double setVely;

            // depending on if its above or below
            if (y1 > y2){
                // above
                setVely = -100;
            }
            else{
                // below
                setVely = 100;
            }
            // sets attributes early
            Ballmain.initialPower = THREE;
            Ballmain.velx = setVelx * Ballmain.initialPower;
            Ballmain.vely = setVely * Ballmain.initialPower;

            return;
        }
        else if (y2 - y1 == 0){
            // horizontal line

            // sets vely to 0
            double setVelx;
            double setVely = 0;

            if (x1 > x2){
                // right
                setVelx = -100;
            }
            else{
                // left
                setVelx = 100;
            }

            // sets attributes early
            Ballmain.initialPower = THREE;
            Ballmain.velx = setVelx * Ballmain.initialPower;
            Ballmain.vely = setVely * Ballmain.initialPower;

            return;
        }


        float m = (y2-y1 + 0.0f) / (x2-x1);
        float b1 = y1-(x1 * m);

        double a = -m;
        float b = 1;
        double c = -b1;

        int r = 20;

        double a2 = 1 + m*m;
        double b2 = (-x1 * 2) + ( (m * (b1 - y1)) * 2);
        double c2 = (x1 * x1 + ((b1-y1) * (b1-y1)) - (r * r));

        double x0 = -a2*c2/(a2*a2+b2*b2), y0 = -b2*c2/(a2*a2+b2*b2);

        double d = r*r - c2*c2/(a2*a2+b2*b2);
        double mult = sqrt (d / (a2*a2+b2*b2));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        double xPos = (-(b2) + sqrt(pow(b2, 2) - 4 * (a2) * (c2))) / (2 * a2);
        double xNeg = (-(b2) - sqrt(pow(b2, 2) -4 * (a2) * (c2))) / (2 * a2);

        double yPoint = m * (xPos) + b1;
        double ypoint2 = m * (xNeg) + b1;

        // distance between main ball and the points
        double d1 = sqrt( pow((xPos - Ballmain.x), 2) + pow((yPoint - Ballmain.y), 2) );
        double d2 = sqrt( pow((xNeg - Ballmain.x), 2) + pow((ypoint2 - Ballmain.y), 2) );

        /// REMOVE
        if (d1 > d2){
            Rendermain.xCord = xNeg;
            Rendermain.yCord = ypoint2;

            Rendermain.xCord2 = xPos;
            Rendermain.yCord2 = yPoint;
        }
        else{
            Rendermain.xCord = xPos;
            Rendermain.yCord = yPoint;

            Rendermain.xCord2 = xNeg;
            Rendermain.yCord2 = ypoint2;
        }

        // distance between the goal and the two points used to determine which is the first and second collision point
        double d1_ = sqrt( pow((Rendermain.xCord - closestGoal.x), 2) + pow((Rendermain.yCord - closestGoal.y), 2) );
        double d2_ = sqrt( pow((Rendermain.xCord2  - closestGoal.x), 2) + pow((Rendermain.yCord2 - closestGoal.y), 2) );

        // if the point closest to the ball is the first collision then it should not attempt scoring that ball
        if (d1_< d2_){
            balls.erase(balls.begin() + inno);
            continue;
        }




        x1 = Rendermain.xCord;
        y1 = Rendermain.yCord;

        a2 = 1 + m*m;
        b2 = (-x1 * 2) + ( (m * (b1 - y1)) * 2);
        c2 = (x1 * x1 + ((b1-y1) * (b1-y1)) - (r * r));

        x0 = -a2*c2/(a2*a2+b2*b2), y0 = -b2*c2/(a2*a2+b2*b2);

        d = r*r - c2*c2/(a2*a2+b2*b2);
        mult = sqrt (d / (a2*a2+b2*b2));

        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        xPos = (-(b2) + sqrt(pow(b2, 2) - 4 * (a2) * (c2))) / (2 * a2);
        xNeg = (-(b2) - sqrt(pow(b2, 2) -4 * (a2) * (c2))) / (2 * a2);

        yPoint = m * (xPos) + b1;
        ypoint2 = m * (xNeg) + b1;

        d1 = sqrt( pow((xPos - Ballmain.x), 2) + pow((yPoint - Ballmain.y), 2) );
        d2 = sqrt( pow((xNeg - Ballmain.x), 2) + pow((ypoint2 - Ballmain.y), 2) );

        /// REMOVE
        if (d1 > d2){
            Rendermain.xCord_ = xNeg;
            Rendermain.yCord_ = ypoint2;

            Rendermain.xCord2_ = xPos;
            Rendermain.yCord2_ = yPoint;
        }
        else{
            Rendermain.xCord_ = xPos;
            Rendermain.yCord_ = yPoint;

            Rendermain.xCord2_ = xNeg;
            Rendermain.yCord2_ = ypoint2;
        }

        if (Rendermain.xCord == closestBall.x && Rendermain.yCord == closestBall.y){
            balls.erase(balls.begin() + inno);
            continue;
        }
        double distanceX_1 = Rendermain.xCord_  - Ballmain.x ;
        double distanceY_1 = Rendermain.yCord_  - Ballmain.y;
        double distance_direct_1 = sqrt((distanceX_1 * distanceX_1) + (distanceY_1 * distanceY_1)); // pythagoras

        float vectorX_1 = distanceX_1 * (speed / distance_direct_1);
        float vectorY_1 = distanceY_1 * (speed / distance_direct_1);

        // multiplies each value by 600 and sets that the velocity
        float setVelx = vectorX_1 * 600;
        float setVely = vectorY_1 * 600;


        /// sets power

        // since all values are going to be between 0 and 1 the power will be chosen respectively
        // so if its between 0 and 0.2 it will be one power and etc

        power setPower = NONE;


        /// sets velx and vely




        // sets all attributes
        Ballmain.initialPower = ONE;
        Ballmain.velx = setVelx * Ballmain.initialPower;
        Ballmain.vely = setVely * Ballmain.initialPower;
        break;
    }


}


#endif //POOL_GETINPUTS_H
