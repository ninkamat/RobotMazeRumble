//
//  RobotClass3D.h
//  RoboMazeRumble3D
//
//  Created by Ninad Kamat on 11/27/15.
//  Copyright © 2015 2b||!2b. All rights reserved.
//

#ifndef ROBOTCLASS_H_IS_INCLUDED
#define ROBOTCLASS_H_IS_INCLUDED

#include <stdio.h>
#include "fssimplewindow.h"
#include "Astar.h"
#include <math.h>

const double PI = 3.1415962;

class Robot
{
protected:
    int size;
    double px, py, pz;
    double framesize;
public:
    Robot();
};

class HumanRobot :public Robot
{
protected:
    double h, p, b;
    double fov, nearZ, farZ;
    int size;
    int *map;
    void GetForwardVector(double &vx,double &vy,double &vz);
    int GetWall(int bx,int bz);
    bool DontGoInWall();
public:
    double speed;
    HumanRobot(int n, const int *mapin);
    void Move(int key);
    void Draw(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);
    bool CheckTarget();
};

class ComputerRobot :public Robot
{
public:
    std::vector <Vec2> path;
    void Move(void);
    void Draw(void);
    ComputerRobot(int n);
    bool CheckTarget();
    void Print();
};


#endif /* RobotClass_hpp */
