//
//  RMRGame3D.h
//  RoboMazeRumble3D
//
//  Created by Ninad Kamat on 11/20/15.
//  Copyright © 2015 2b||!2b. All rights reserved.
//

#ifndef RMRGAME_H_IS_INCLUDED
#define RMRGAME_H_IS_INCLUDED

#include <stdio.h>
#include "maze3D.h"
#include "fssimplewindow.h"
#include "Robotclass3D.h"
#include "Menu3D.h"

class Game
{
private:
    Game(const Game &incoming){}
    Game &operator=(const Game &incoming){return *this;}
protected:
    int level, score;
    bool TargetReached;

    int OneLevel(GLuint textID[]);
    int EndLevel(GLuint textID[]);
public:
    Game(int level, int score);
    bool Run(GLuint textID []);
    int GetLevel();
    int GetScore();
};

#endif /* RMRGame_hpp */
