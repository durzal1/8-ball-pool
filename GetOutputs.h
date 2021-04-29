//
// Created by zacky on 4/29/2021.
//

#ifndef POOL_GETINPUTS_H
#define POOL_GETINPUTS_H

#include "ball.h"
#include "goal.h"
//// gets the inputs
std::vector<double> geOutputs(ball Ballmain, std::vector<goal> Goals ){
    /// finds the closest ball

// vector of distances
    std::vector<float> distances;

// loops through each ball and finds the distance between it and white ball
    for (ball &b:ball::balls){
// if its the white ball it goes next
        if (b.innovation == 1) continue;

// distance formula
        double dist = sqrt( pow((b.x - Ballmain.x), 2) + pow((b.y - Ballmain.y), 2) );

// adds the dist to distances vector
        distances.push_back(dist);
    }


// finds the lowest distance
    auto distMin = (*min_element(distances.begin(), distances.end()));

// gets the index
    auto it = std::find(distances.begin(), distances.end(), distMin);
    int index = it- distances.begin();

// sets the closet ball
    ball closestBall = Ballmain.balls[index + 1];

// distance optamized to work with neat
    double distMinOpt = (distMin / 10) / 178;
    double distMinOpt2 = pow(0.9, distMin / 10);



// finds the angle between the white ball and closest ball

    float delta_x = (closestBall.x) - Ballmain.x;
    float delta_y =(closestBall.y) - Ballmain.x;

// angle in radians
    double thetaRadiansBall = atan2(delta_y, delta_x);


/// finds the closest goal to closest ball

// vector of distances
    std::vector<float> distancesGoals;

    for (goal g:Goals){
// distance formula
        double dist = sqrt( pow((g.x - closestBall.x), 2) + pow((g.y - closestBall.y), 2) );

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
    double distMinOptGoal = (distMinGoal / 10) / 178;
    double distMinOpt2Goal = pow(0.9, distMinGoal / 10);


// angle between closest ball and its closest goal

    float delta_x2 = (closestGoal.x) - closestBall.x;
    float delta_y2 =(closestGoal.y) - closestBall.x;

// angle in radians
    double thetaRadiansGoal = atan2(delta_y2, delta_x2);


// vector of all inputs
    std::vector<double> inputs {distMinOpt2, thetaRadiansBall, distMinOpt2Goal, thetaRadiansGoal};

    return inputs;
}


#endif //POOL_GETINPUTS_H
