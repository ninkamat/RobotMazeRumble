#ifndef MAZE_H_IS_INCLUDED
#define MAZE_H_IS_INCLUDED

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Astar.h"
#include "fssimplewindow.h"
#include "yspng.h"

class Maze
{
private:
    Maze &operator=(const Maze &from){return *this;};
    Maze(const Maze &from){};

protected:
    int *m, n, *state;
    void GiveMaze();
    int PickRandomIndex();
    bool CheckFull();
    bool CheckNeighbour(int i, int j);
    bool CheckState(int i, int j);
    void SetMaze();
    
public:
    Maze(int a);
    ~Maze();
    void CleanUp();
    void GenerateMaze(Astar &champ);
    const int GetDimension();
    const int *GetPointer() const;
    void Draw2d();
    const void Draw3D(GLuint txt[]);
    const void DrawCube(double x, double z, GLuint txt);
    void DrawWall(GLuint txt);
    void TextureMapping(GLuint txt[]);
};

#endif