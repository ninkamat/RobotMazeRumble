//
//  Astar.h
//  OpenGLFramework
//
//  Created by Ninad Kamat on 12/4/15.
//  Copyright © 2015 CMU. All rights reserved.
//

#ifndef ASTAR_H_IS_INCLUDED
#define ASTAR_H_IS_INCLUDED

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class Vec2
{
public:
    int x,y;
    void Set(int i, int j);
    Vec2();
    Vec2(int i, int j);
};

class Node
{
public:
    int f, g, h, pixvalue;
    bool visited;
    Vec2 index;
    Node();
    bool operator>(const Node &x) const;
    bool operator<(const Node &x) const;
};

class Astar
{
    Node *map;
    int msize;
    std::vector<Vec2> path;
public:
    Astar();
    void initialize(const int n, const int *maze);
    ~Astar();
    void Cleanup();
    bool CalculateG(const int n, const int *maze);
    void PrintG();
    std::vector<Vec2> GetPath();
};

#endif /* Astar_h */
