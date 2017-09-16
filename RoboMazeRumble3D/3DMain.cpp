#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
//#include "droid.h"
#include "maze.h"
#include "RobotClass.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"


using namespace std;
/*
class CameraObject
{
public:
    double x,y,z;
    double h,p,b;
    int size,*m;
    
    double fov,nearZ,farZ;
    
    CameraObject(int n,const int *p);
    ~CameraObject();
    void CleanUp();
    void Initialize(const int *p);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);
    void GetForwardVector(double &vx,double &vy,double &vz);
    int GetWall(int bx,int bz);
    bool DontGoInWall(double x, double z);
    bool CheckTarget(double x,double z);
    //void TextureMapping(GLuint txt[]);
};

CameraObject::CameraObject(int n, const int *p)
{
    x=10;
    y=5;
    z=(n+0.5)*20.0;
    h=0;
    p=0;
    b=0;
    size = 2*n+1;
    fov=YsPi/3.0;  // 60 degree
    nearZ=1.0;
    farZ=1000.0;
    
}

void CameraObject::Initialize(const int *p)
{
    m=nullptr;
    m = new int[size*size];
    for(int i=0;i<size*size;i++)
    {
        m[i]=p[i];
    }
}

CameraObject::~CameraObject()
{
    CleanUp();
}

void CameraObject::CleanUp()
{
    if(m!=nullptr)
    {
       delete [] m;
        m=nullptr;
    }size=0;x=0,y=0;z=0;
    h=0;p=0;b=0;fov=0;nearZ=0;farZ=0;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;
    
    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

int CameraObject::GetWall(int bx,int bz)
{
    if(0<=bx && bx<size && 0<=bz && bz<size)
    {
        return m[bz*size+bx];
    }
    return ' ';
}

bool CameraObject::DontGoInWall(double x, double z)
{
    if(GetWall(int(x/20.0),int(z/20.0))==0 ||
       GetWall(int((x-1.5)/20.0),int((z-1.5)/20.0))==0 ||
       GetWall(int((x+1.5)/20.0),int((z-1.5)/20.0))==0 ||
       GetWall(int((x-1.5)/20.0),int((z+1.5)/20.0))==0 ||
       GetWall(int((x+1.5)/20.0),int((z+1.5)/20.0))==0 ||
       (x-1.5)<=0||(x+1.5)>=size*20||(z-1.5)<=0||(z+1.5)>=(size*20))
    {
        return true;
    }else
    {
        return false;
    }
}

bool CameraObject::CheckTarget(double x, double z)
{
    if(GetWall(int(x/20.0),int(z/20.0))==3 ||
       GetWall(int((x-0.5)/20.0),int((z-0.5)/20.0))==3 ||
       GetWall(int((x+0.5)/20.0),int((z-0.5)/20.0))==3 ||
       GetWall(int((x-0.5)/20.0),int((z+0.5)/20.0))==3 ||
       GetWall(int((x+0.5)/20.0),int((z+0.5)/20.0))==3 )
    {
        return true;
    }else
    {
        return false;
    }

}

void CameraObject::TextureMapping(GLuint txt[])
{
    YsRawPngDecoder png[3];
    png[0].Decode("Brick.png");
    png[0].Flip();
    
    glGenTextures(1,&txt[0]);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D,txt[0]);  // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glTexImage2D
    (GL_TEXTURE_2D,
     0,    // Level of detail
     GL_RGBA,
     png[0].wid,
     png[0].hei,
     0,    // Border width, but not supported and needs to be 0.
     GL_RGBA,
     GL_UNSIGNED_BYTE,
     png[0].rgba);
    
    ///////////////////////////////////////////////////////////////////////

    png[1].Decode("Sky2.png");
    png[1].Flip();
    
    glGenTextures(1,&txt[1]);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D,txt[1]);  // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glTexImage2D
    (GL_TEXTURE_2D,
     0,    // Level of detail
     GL_RGBA,
     png[1].wid,
     png[1].hei,
     0,    // Border width, but not supported and needs to be 0.
     GL_RGBA,
     GL_UNSIGNED_BYTE,
     png[1].rgba);

    ///////////////////////////////////////////////////////////////////////

    png[2].Decode("Floor.png");
    png[2].Flip();
    
    glGenTextures(1,&txt[2]);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D,txt[2]);  // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glTexImage2D
    (GL_TEXTURE_2D,
     0,    // Level of detail
     GL_RGBA,
     png[2].wid,
     png[2].hei,
     0,    // Border width, but not supported and needs to be 0.
     GL_RGBA,
     GL_UNSIGNED_BYTE,
     png[2].rgba);
    
}
*/
int main(void)
{
    srand((int)time(NULL));
    Maze a(7);
    a.GenerateMaze();
    int terminate=0;
    HumanRobot h(a.GetDimension(),a.GetPointer());
    ComputerRobot c(a.GetDimension(),a.GetPointer());
    c.AStar();
    
    FsOpenWindow(16,16,1200,800,1);
    GLuint txt[3];
    a.TextureMapping(txt);
    int cycle = 0;
    while(0==terminate)
    {
        FsPollDevice();
        
        int wid,hei;
        FsGetWindowSize(wid,hei);
        
        int key=FsInkey();
        switch(key)
        {
            case FSKEY_ESC:
                terminate=1;
                break;
        }
        
        h.Move(key);
        cycle++;
        if (cycle%20==0)
            c.Move();
        if(h.CheckTarget()==true||c.CheckTarget()==true)
        {
          terminate=1;
        }
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glViewport(0,0,wid,hei);

        // Set up 3D drawing
        h.SetUpCameraProjection();
        h.SetUpCameraTransformation();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1,1);

        // 3D drawing from here
		//stl.Draw(camera.x,camera.z);
        a.Draw3D(txt);

        // Set up 2D drawing
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        a.Draw2d();
        h.Draw();
        c.Draw();
        // 2D drawing from here

        FsSwapBuffers();
        FsSleep(10);
    }

    return 0;

}
//24-783
