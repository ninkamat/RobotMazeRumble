//
//  RobotClass3D.cpp
//  RoboMazeRumble3D
//
//  Created by Ninad Kamat on 11/27/15.
//  Copyright © 2015 2b||!2b. All rights reserved.
//

#include "RobotClass3D.h"


//////////////////////////////////////////////////////////////////////////////////
//ROBOT DEFINITION BEGINS

Robot::Robot()
{
    px = 10.;
    py = 5.;
    pz = 10.;
    size = 0;
    framesize = 400.0;
}

//////////////////////////////////////////////////////////////////////////////////
//HUMAN ROBOT DEFINITION BEGINS

HumanRobot::HumanRobot(int n, const int *mapin)
{
    size = 2*n + 1;
    pz = 20.0*n+10.0;
    framesize = n==37?450.0:400.0;
    map = new int[size*size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            map[i + j*size] = mapin[i + j*size];
        }
    }
    speed = 675/size;
    h = 0.0;
    p = 0.0;
    b = 0.0;
    fov = PI/3.0;
    nearZ = 1.0;
    farZ = 1000.0;
}

void HumanRobot::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;
    
    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/PI,aspect,nearZ,farZ);
}

void HumanRobot::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/PI,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/PI,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/PI,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-px,-py,-pz);
}

void HumanRobot::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

int HumanRobot::GetWall(int bx,int bz)
{
    if(0<=bx && bx<size && 0<=bz && bz<size)
    {
        return map[bz*size+bx];
    }
    return ' ';
}

bool HumanRobot::DontGoInWall()
{
    if(GetWall(int(px/20.0),int(pz/20.0))==0 ||
       GetWall(int((px-1.5)/20.0),int((pz-1.5)/20.0))==0 ||
       GetWall(int((px+1.5)/20.0),int((pz-1.5)/20.0))==0 ||
       GetWall(int((px-1.5)/20.0),int((pz+1.5)/20.0))==0 ||
       GetWall(int((px+1.5)/20.0),int((pz+1.5)/20.0))==0 ||
       (px-1.5)<=0||(px+1.5)>=size*20||(pz-1.5)<=0||(pz+1.5)>=(size*20))
    {
        return true;
    }else
    {
        return false;
    }
}

bool HumanRobot::CheckTarget()
{
    if(GetWall(int(px/20.0),int(pz/20.0))==3 ||
       GetWall(int((px-0.5)/20.0),int((pz-0.5)/20.0))==3 ||
       GetWall(int((px+0.5)/20.0),int((pz-0.5)/20.0))==3 ||
       GetWall(int((px-0.5)/20.0),int((pz+0.5)/20.0))==3 ||
       GetWall(int((px+0.5)/20.0),int((pz+0.5)/20.0))==3 )
    {
        return true;
    }else
    {
        return false;
    }
    
}

void HumanRobot::Draw(void)
{
    double r = framesize/double(3*size);
    double pixel = framesize/(double)size;
    double factor = pixel/20.0;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor4ub(0, 0, 255,200);
    
    glBegin(GL_QUADS);
    glVertex2d(factor*(px)-r, factor*(pz)-r);
    glVertex2d(factor*(px)-r, factor*(pz)+r);
    glVertex2d(factor*(px)+r, factor*(pz)+r);
    glVertex2d(factor*(px)+r, factor*(pz)-r);
    glEnd();
    glDisable(GL_BLEND);
}

void HumanRobot::Move(int key)
{
    double vx,vy,vz;
    const double prevx=px;
    const double prevz=pz;
    if(FsGetKeyState(FSKEY_UP)==0)
    {
        GetForwardVector(vx,vy,vz);
        px-=vx*1.5;
        py-=vy*1.5;
        pz-=vz*1.5;
    }
    if(FsGetKeyState(FSKEY_DOWN)==0)
    {
        GetForwardVector(vx,vy,vz);
        px+=vx*1.5;
        py+=vy*1.5;
        pz+=vz*1.5;
    }
    if(FsGetKeyState(FSKEY_LEFT)==0)
    {
        h-=PI/60.0;
    }
    if(FsGetKeyState(FSKEY_RIGHT)==0)
    {
        h+=PI/60.0;
    }
    if(DontGoInWall()==true)
    {
        px=prevx;
        pz=prevz;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//COMPUTER ROBOT DEFINITION BEGINS

ComputerRobot::ComputerRobot(int n)
{
    size = 2*n+1;
    framesize = n==37?450.0:400.0;
    pz = 20.0*n+10.0;
}

void ComputerRobot::Draw(void)
{
    double r = framesize/double(3*size);
    double pixel = framesize/(double)size;
    double factor = pixel/20.0;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4ub(255, 0, 255,200);
    
    glBegin(GL_QUADS);
    glVertex2d(factor*(px)-r, factor*(pz)-r);
    glVertex2d(factor*(px)-r, factor*(pz)+r);
    glVertex2d(factor*(px)+r, factor*(pz)+r);
    glVertex2d(factor*(px)+r, factor*(pz)-r);
    glEnd();
    
    glDisable(GL_BLEND);
}

void ComputerRobot::Move()
{
    double tx = 20.;
    double ty = 20.;
    if (path.size()!=0)
    {
        auto p = path.back();
        px = p.x*tx+tx/2;
        pz = p.y*ty+ty/2;
        path.pop_back();
    }
}

bool ComputerRobot::CheckTarget()
{
    if (((size-1)*20)<=px && px<=(size*20) && ((size/2)*20)<=pz && pz<=((size/2+1)*20))
        return true;
    return false;
}

void ComputerRobot::Print()
{
    for (auto i : path)
        printf("(%d %d)\n",i.x, i.y);
}
