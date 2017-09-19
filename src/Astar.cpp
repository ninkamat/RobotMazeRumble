//
//  Astar.cpp
//  OpenGLFramework
//
//  Created by Ninad Kamat on 12/4/15.
//  Copyright © 2015 CMU. All rights reserved.
//

#include "Astar.h"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(int i, int j)
{
    Set(i, j);
}

void Vec2::Set(int i, int j)
{
    x = i;
    y = j;
}

Node::Node()
{
    g = 500;
    h = 0;
    f = g+h;
    pixvalue = 0;
    index.x=0;
    index.y = 0;
    visited = false;
}

bool Node::operator>(const Node &x) const
{
    return this->f>x.f;
}

bool Node::operator<(const Node &x) const
{
    return this->f<x.f;
}

Astar::Astar()
{
    map = nullptr;
}

void Astar::Cleanup()
{
    if (map!=nullptr)
        delete [] map;
    map = nullptr;
    msize = 0;
}

void Astar::initialize(const int n, const int *maze)
{
    Cleanup();
    msize = 2*n+1;
    map = new Node [msize*msize];
    for (int i = 0; i<msize*msize; i++)
    {
        map[i].pixvalue = maze[i];
        map[i].index.x = i%msize;
        map[i].index.y = i/msize;
        if (maze[i] == 0)
            map[i].visited = true;
    }
}

Astar::~Astar()
{
    Cleanup();
}

bool Astar::CalculateG(const int n, const int *maze)
{
    initialize(n,maze);
    int iteration = 0;
    int x = 0, y= msize/2;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> todo;
    map[y*msize+x].g = 0;
    map[y*msize+x].h = std::abs(msize-1-x) + std::abs(msize/2-y);
    map[y*msize+x].f = map[y*msize+x].g + map[y*msize+x].h;
    todo.push(map[y*msize+x]);
    while(todo.empty()!=true)
    {
        iteration++;
        auto p = todo.top();
        x = p.index.x;
        y = p.index.y;
        todo.pop();
        map[y*msize+x].visited = true;
        if (!(x == (msize-1) && y == (msize/2)))
        {
            if(0<=x && x<msize && 0<=y && y<msize)
            {
                if (x!=0 && map[y*msize+(x-1)].pixvalue != 0 && map[y*msize+(x-1)].visited != true)
                {
                    map[y*msize+(x-1)].g = map[y*msize+x].g + 1;
                    map[y*msize+(x-1)].h = std::abs(msize-1-(x-1)) + std::abs(msize/2-y);
                    map[y*msize+(x-1)].f = map[y*msize+(x-1)].g + map[y*msize+(x-1)].h;
                    todo.push(map[y*msize+(x-1)]);
                }
                if (x!=(msize-1) && map[y*msize+(x+1)].pixvalue != 0 && map[y*msize+(x+1)].visited != true)
                {
                    map[y*msize+(x+1)].g = map[y*msize+x].g + 1;
                    map[y*msize+(x+1)].h = std::abs(msize-1-(x+1)) + std::abs(msize/2-y);
                    map[y*msize+(x+1)].f = map[y*msize+(x+1)].g + map[y*msize+(x+1)].h;
                    todo.push(map[y*msize+(x+1)]);
                }
                if (y!=0 && map[(y-1)*msize+x].pixvalue != 0 && map[(y-1)*msize+x].visited != true)
                {
                    map[(y-1)*msize+x].g = map[y*msize+x].g + 1;
                    map[(y-1)*msize+x].h = std::abs(msize-1-x) + std::abs(msize/2-(y-1));
                    map[(y-1)*msize+x].f = map[(y-1)*msize+x].g + map[(y-1)*msize+x].h;
                    todo.push(map[(y-1)*msize+x]);
                }
                if (y!=(msize-1) && map[(y+1)*msize+x].pixvalue != 0 && map[(y+1)*msize+x].visited != true)
                {
                    map[(y+1)*msize+x].g = map[y*msize+x].g + 1;
                    map[(y+1)*msize+x].h = std::abs(msize-1-x) + std::abs(msize/2-(y+1));
                    map[(y+1)*msize+x].f = map[(y+1)*msize+x].g + map[(y+1)*msize+x].h;
                    todo.push(map[(y+1)*msize+x]);
                }
            }
        }
        else
        {
            break;
        }
    }
    //printf("%d iterations\n",iteration);
    if (todo.empty()==true)
        return false;
    return true;
}

void Astar::PrintG()
{
    for (int i = 0; i<msize; i++)
    {
        for (int j = 0; j<msize; j++)
            printf("%d\t", map[i*msize+j].pixvalue);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i<msize; i++)
    {
        for (int j = 0; j<msize; j++)
            printf("%d\t", map[i*msize+j].g);
        printf("\n");
    }
    printf("\n");
}

std::vector<Vec2> Astar::GetPath()
{    
    int x = msize-1;
    int y = msize/2;
    Vec2 minindex(x,y);
    path.push_back(minindex);
    int min = map[y*msize+x].g;
    while (min!=0)
    {
        if (x!=0 && map[y*msize+(x-1)].pixvalue != 0)
        {
            if (map[y*msize+(x-1)].g<=min)
            {
                min = map[y*msize+(x-1)].g;
                minindex.Set (x-1,y);
            }
        }
        if (x!=(msize-1) && map[y*msize+(x+1)].pixvalue != 0)
        {
            if (map[y*msize+(x+1)].g<=min)
            {
                min = map[y*msize+(x+1)].g;
                minindex.Set (x+1,y);
            }
        }
        if (y!=0 && map[(y-1)*msize+x].pixvalue != 0)
        {
            if (map[(y-1)*msize+x].g<=min)
            {
                min = map[(y-1)*msize+x].g;
                minindex.Set (x,y-1);
            }
        }
        if (y!=(msize-1) && map[(y+1)*msize+x].pixvalue != 0)
        {
            if (map[(y+1)*msize+x].g<=min)
            {
                min = map[(y+1)*msize+x].g;
                minindex.Set (x,y+1);
            }
        }
        if (x != minindex.x || y != minindex.y)
        {
            x = minindex.x;
            y = minindex.y;
            path.push_back(minindex);
        }
        else
        {
            break;
        }
    }
    return path;
}
