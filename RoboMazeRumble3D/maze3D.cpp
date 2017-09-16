//
//  maze3D.cpp
//  RoboMazeRumble
//
//  Created by Akash Sambrekar on 11/13/15.
//  Copyright © 2015 CMU. All rights reserved.
//
#include "maze3D.h"

using namespace std;

Maze::Maze(int a)
{
    n=a;
    m = new int [(2*n+1)*(2*n+1)];
    for (int i=0;i<(2*n+1);++i)
    {
        for(int j=0;j<(2*n+1);++j)
        {
            if(i%2==1&&j%2==1)
            {
                m[i*(2*n+1)+j]=0;
            }else
            {
                m[i*(2*n+1)+j]=1;
            }
        }
    }
    state = new int [n*n];
    for(int i=0;i<n*n;++i)
    {
        state[i]=0;
    }
}

Maze::~Maze()
{
    CleanUp();
}

void Maze::CleanUp()
{
    if(m!=nullptr)
    {
        delete [] m;
        delete [] state;
        m=nullptr;state=nullptr;
    }
    n=0;
}

bool Maze::CheckFull()
{
    for(int i=0;i<n*n;i++)
    {
        if(0==state[i])
        {
            return false;
        }
    }
    return true;
}

bool Maze::CheckState(int i,int j)
{
    return (state[i*n+j]==0);
}

bool Maze::CheckNeighbour(int i, int j)
{
    if(i!=(n-1))
    {
        if (CheckState(i+1, j)==true)
            return true;
        
    }
    if(i!=0)
    {
        if (CheckState(i-1,j) == true)
            return true;
    }
    if(j!=(n-1))
    {
        if (CheckState(i,j+1) == true)
            return true;
    }
    if(j!=0)
    {
        if (CheckState(i,j-1) == true)
            return true;
    }
    return false;
    
}

int Maze::PickRandomIndex()
{
    return rand()%n;
}

void Maze::GiveMaze()
{
    srand((int)time(NULL));
    int i,j,k;
    SetMaze();
    while(CheckFull()==false)
    {
        i = PickRandomIndex();
        j = PickRandomIndex();
        
        if(CheckState(i,j)==true)
        {
            state[i*n+j]=1;
            
            while(true==CheckNeighbour(i,j))
            {
                
            DUDE:int a = rand()%4;
                switch(a)
                {
                    case 0:
                        if(i!=(n-1)&&true==CheckState(i+1,j))
                        {
                            i++;state[i*n+j]=1;
                            k = (2*i+1)*(2*n+1)+(2*j+1);
                            m[k-(2*n+1)]=0;
                        }else
                        {
                            goto DUDE;
                        }
                        break;
                    case 1:
                        if(i!=0&&true==CheckState(i-1,j))
                        {
                            i--;state[i*n+j]=1;
                            k = (2*i+1)*(2*n+1)+(2*j+1);
                            m[k+(2*n+1)]=0;
                        }else
                        {
                            goto DUDE;
                        }
                        break;
                    case 2:
                        if(j!=0&&true==CheckState(i,j-1))
                        {
                            j--;state[i*n+j]=1;
                            k = (2*i+1)*(2*n+1)+(2*j+1);
                            m[k+1]=0;
                        }else
                        {
                            goto DUDE;
                        }
                        break;
                    case 3:
                        if(j!=(n-1)&&true==CheckState(i,j+1))
                        {
                            j++;state[i*n+j]=1;
                            k = (2*i+1)*(2*n+1)+(2*j+1);
                            m[k-1]=0;
                        }else
                        {
                            goto DUDE;
                        }
                        break;
                        
                }
                m[(n)*(2 * n + 1)] = 2;
                m[(n)*(2 * n + 1) + (2 * n)] = 3;
                
                if (n > 5)
                {
                    m[0] = 0;
                    m[1] = 0;
                    m[2 * n + 1] = 0;
                    
                    m[(2 * n)] = 0;
                    m[(2 * n) - 1] = 0;
                    m[(2 * n + 1) + 2 * n] = 0;
                    
                    m[(2 * n)*(2 * n + 1)] = 0;
                    m[(2 * n - 1)*(2 * n + 1)] = 0;
                    m[(2 * n)*(2 * n + 1) + 1] = 0;
                    
                    m[(2 * n - 1)*(2 * n + 1) + (2 * n)] = 0;
                    m[(2 * n)*(2 * n + 1) + (2 * n)] = 0;
                    m[(2 * n)*(2 * n + 1) + (2 * n) - 1] = 0;
                }
                m[n] = 0;
                m[(2 * n)*(2 * n + 1) + (n)] = 0;
                
            }
            
        }
    }
}

void Maze::Draw2d()
{
    double k=4;
    switch(n)
    {
        case 7:
            k = 400. / double(2*n + 1);
            break;
        case 12:
            k = 400. / double(2*n + 1);
            break;

        case 22:
            k = 400. / double(2*n + 1);
            break;

        case 37:
            k = 450. / double(2*n + 1);
            break;

    }
    
    if(nullptr!=m)
    {
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);
        for(int i=0;i<(2*n+1);i++)
        {
            for(int j=0;j<(2*n+1);j++)
            {
                switch(m[i*(2*n+1)+j])
                {
                    case 0://BLACK
                        glColor4ub(0,0,0,128);
                        break;
                        
                    case 1://YELLO
                        glColor4ub(255,255,0,128);
                        break;
                        
                    case 2://RED
                        glColor4ub(255,0,0,128);
                        break;
                        
                    case 3://GREEN
                        glColor4ub(0,255,0,128);
                        break;
                        
                }
                glVertex2d(double(j)*k,     double(i)*k);
                glVertex2d(double(j)*k+k,   double(i)*k);
                glVertex2d(double(j)*k+k, double(i)*k+k);
                glVertex2d(double(j)*k,   double(i)*k+k);
            }
        }
        glEnd();
        glDisable(GL_BLEND);
    }
    
}

const void Maze::Draw3D(GLuint txt[])
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPEAT);
    glColor4d(1.0,1.0,1.0,1.0);
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,txt[2]);

    if(nullptr!=m)
    {
        glBegin(GL_QUADS);
        for(int i=0;i<(2*n+1);i++)
        {
            for(int j=0;j<(2*n+1);j++)
            {
                if(m[i*(2*n+1)+j]==1)
                {
                    
                    glTexCoord2d(0.0,0.0);
                    glVertex3d(j*20   ,0,   i*20);
                    glTexCoord2d(1.0,0.0);
                    glVertex3d(j*20+20,0,   i*20);
                    glTexCoord2d(1.0,1.0);
                    glVertex3d(j*20+20,0,   (i*20+20));
                    glTexCoord2d(0.0,1.0);
                    glVertex3d(j*20   ,0,   (i*20+20));
                }
            }
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        int i = n,j=0;
        
        if(m[i*(2*n+1)+j]==2)
        {
            glBegin(GL_QUADS);
            glColor3ub(255,0,0);
            glVertex3i(j*20   ,0,   i*20);
            glVertex3i(j*20+20,0,   i*20);
            glVertex3i(j*20+20,0,   (i*20+20));
            glVertex3i(j*20   ,0,   (i*20+20));
            glEnd();
            
        }
        i=n;j=2*n;
        if(m[i*(2*n+1)+j]==3)
        {
            glBegin(GL_QUADS);
            glColor3ub(0,255,0);
            glVertex3i(j*20   ,0,   i*20);
            glVertex3i(j*20+20,0,   i*20);
            glVertex3d(j*20+20,0,   (i*20+20));
            glVertex3d(j*20   ,0,   (i*20+20));
            glEnd();
        }
    }
    
    DrawWall(txt[0]);
    
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPEAT);
    glColor4d(1.0,1.0,1.0,1.0);
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,txt[1]);

    glBegin(GL_QUADS);
    
    glTexCoord2d(0.0,0.0);
    glVertex3d(0.0,        20.0,        0.0);
    glTexCoord2d(1.0,0.0);
    glVertex3d((2*n+1)*20, 20.0,        0.0);
    glTexCoord2d(1.0,1.0);
    glVertex3d((2*n+1)*20, 20.0, (2*n+1)*20);
    glTexCoord2d(0.0,1.0);
    glVertex3d(0.0,        20.0, (2*n+1)*20);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    
}

const void Maze::DrawCube(double x, double z, GLuint txt)
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPEAT);
    glColor4d(1.0,1.0,1.0,1.0);
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,txt);
    
    glBegin(GL_QUADS);
    
    glVertex3d(x*20,     0,     z*20);
    glVertex3d(x*20+20,  0,     z*20);
    glVertex3d(x*20+20,  0,(z*20+20));
    glVertex3d(x*20,     0,(z*20+20));
    
    glVertex3d(x*20,     20,     z*20);
    glVertex3d(x*20+20  ,20,     z*20);
    glVertex3d(x*20+20  ,20, (z*20+20));
    glVertex3d(x*20,     20, (z*20+20));
    
    
    glTexCoord2d(0.0,0.0);
    glVertex3d(x*20,     0, (z*20+20+0.0001));
    glTexCoord2d(1.0,0.0);
    glVertex3d(x*20+20,  0, (z*20+20+0.0001));
    glTexCoord2d(1.0,1.0);
    glVertex3d(x*20+20,  20,(z*20+20+0.0001));
    glTexCoord2d(0.0,1.0);
    glVertex3d(x*20,     20,(z*20+20+0.0001));
    
    glTexCoord2d(0.0,0.0);
    glVertex3d(x*20,     0,      (z*20+0.0001));
    glTexCoord2d(1.0,0.0);
    glVertex3d(x*20+20,  0,      (z*20+0.0001));
    glTexCoord2d(1.0,1.0);
    glVertex3d(x*20+20,  20,     (z*20+0.0001));
    glTexCoord2d(0.0,1.0);
    glVertex3d(x*20,     20,     (z*20+0.0001));
    
    glTexCoord2d(0.0,0.0);
    glVertex3d(x*20+0.0001,     0,       z*20);
    glTexCoord2d(1.0,0.0);
    glVertex3d(x*20+0.0001,     0,  (z*20+20));
    glTexCoord2d(1.0,1.0);
    glVertex3d(x*20+0.0001,     20,  (z*20+20));
    glTexCoord2d(0.0,1.0);
    glVertex3d(x*20+0.0001,     20,      z*20);
    
    glTexCoord2d(0.0,0.0);
    glVertex3d(x*20+20+0.0001,     0,      z*20);
    glTexCoord2d(1.0,0.0);
    glVertex3d(x*20+20+0.0001,     0,  (z*20+20));
    glTexCoord2d(1.0,1.0);
    glVertex3d(x*20+20+0.0001,     20, (z*20+20));
    glTexCoord2d(0.0,1.0);
    glVertex3d(x*20+20+0.0001,     20,      z*20);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_LINES);
    
    glColor3ub(0,0,0);
    
    glVertex3i(x*20,     0,     z*20);
    glVertex3i(x*20+20,  0,     z*20);
    glVertex3i(x*20+20,  0,(z*20+20));
    glVertex3i(x*20,     0,(z*20+20));
    
    glVertex3i(x*20,     20,     z*20);
    glVertex3i(x*20+20  ,20,     z*20);
    glVertex3i(x*20+20  ,20, (z*20+20));
    glVertex3i(x*20,     20, (z*20+20));
    
    glVertex3i(x*20,     0, (z*20+20));
    glVertex3i(x*20+20,  0, (z*20+20));
    glVertex3i(x*20+20,  20,(z*20+20));
    glVertex3i(x*20,     20,(z*20+20));
    
    glVertex3i(x*20,     0,      z*20);
    glVertex3i(x*20+20,  0,      z*20);
    glVertex3i(x*20+20,  20,     z*20);
    glVertex3i(x*20,     20,     z*20);
    
    glVertex3i(x*20,     0,       z*20);
    glVertex3i(x*20,     0,  (z*20+20));
    glVertex3i(x*20,     20, (z*20+20));
    glVertex3i(x*20,     20,      z*20);
    
    glVertex3i(x*20+20,     0,       z*20);
    glVertex3i(x*20+20,     0,  (z*20+20));
    glVertex3i(x*20+20,     20, (z*20+20));
    glVertex3i(x*20+20,     20,      z*20);
    
    glEnd();
}

void Maze::DrawWall(GLuint txt)
{
    for(int i=0;i<(2*n+1);i++)
    {
        for(int j=0;j<(2*n+1);j++)
        {
            if(m[i*(2*n+1)+j]==0)
            {
                DrawCube((double)j, (double)i, txt);
            }
        }
    }
    
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_CLAMP);
    glColor4d(1.0,1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,txt);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);
    // glColor3ub(170,170,170);
    glVertex3d(0,0,           0);
    glTexCoord2d(1.0,0.0);
    //glColor3ub(170,170,170);
    glVertex3d(0,0, (2*n+1)*20);
    glTexCoord2d(1.0,1.0);
    //glColor3ub(0,100,200);
    glVertex3d(0,20,(2*n+1)*20);
    glTexCoord2d(0.0,1.0);
    //glColor3ub(0,100,200);
    glVertex3d(0,20,          0);
    //glColor3ub(170,170,170);
    glTexCoord2d(0.0,0.0);
    glVertex3d((2*n+1)*20,0,           0);
    //glColor3ub(170,170,170);
    glTexCoord2d(1.0,0.0);
    glVertex3d((2*n+1)*20,0, (2*n+1)*20);
    //glColor3ub(0,100,200);
    glTexCoord2d(1.0,1.0);
    glVertex3d((2*n+1)*20,20,(2*n+1)*20);
    //glColor3ub(0,100,200);
    glTexCoord2d(0.0,1.0);
    glVertex3d((2*n+1)*20,20,          0);
    //glColor3ub(170,170,170);
    glTexCoord2d(0.0,0.0);
    glVertex3d(0,          0, 0);
    //glColor3ub(170,170,170);
    glTexCoord2d(1.0,0.0);
    glVertex3d((2*n+1)*20, 0, 0);
    //glColor3ub(0,100,200);
    glTexCoord2d(1.0,1.0);
    glVertex3d((2*n+1)*20, 20,0);
    //glColor3ub(0,100,200);
    glTexCoord2d(0.0,1.0);
    glVertex3d(0,          20,0);
    //glColor3ub(170,170,170);
    glTexCoord2d(0.0,0.0);
    glVertex3d(0,          0, (2*n+1)*20);
    //glColor3ub(170,170,170);
    glTexCoord2d(1.0,0.0);
    glVertex3d((2*n+1)*20, 0, (2*n+1)*20);
    //glColor3ub(0,100,200);
    glTexCoord2d(1.0,1.0);
    glVertex3d((2*n+1)*20, 20,(2*n+1)*20);
    //glColor3ub(0,100,200);
    glTexCoord2d(0.0,1.0);
    glVertex3d(0,          20,(2*n+1)*20);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Maze::SetMaze()
{
    for (int i=0;i<(2*n+1);++i)
    {
        for(int j=0;j<(2*n+1);++j)
        {
            if(i%2==1&&j%2==1)
            {
                m[i*(2*n+1)+j]=0;
            }else
            {
                m[i*(2*n+1)+j]=1;
            }
        }
    }
    state = new int [n*n];
    for(int i=0;i<n*n;++i)
    {
        state[i]=0;
    }
}

const int Maze::GetDimension()
{
    return n;
}


const int *Maze::GetPointer(void) const
{
    if(nullptr!=m)
    {
        return m;
    }
    else
    {
        return nullptr;
    }
}

void Maze::GenerateMaze(Astar &champ)
{
    GiveMaze();
    while (champ.CalculateG(n, m) == false)
    {
        SetMaze();
        GiveMaze();
    }
}

void Maze::TextureMapping(GLuint txt[])
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

/////////////////////////////////////////////////////////