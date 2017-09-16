//
//  RoboMazeRumble3D.cpp
//  RoboMazeRumble3D
//
//  Created by Ninad Kamat on 11/20/15.
//  Copyright © 2015 2b||!2b. All rights reserved.
//

#include <stdio.h>
#include "fssimplewindow.h"
#include "RMRGame3D.h"
#include "Menu3D.h"
#include "Tutorial3D.h"

int main()
{
    FsOpenWindow(0, 0, 1200, 800, 1);
    FsChangeToProgramDir();
    
    Menu main;
    GLuint textID[5];
    main.LoadTextures(textID);
    int  i = 0;
    
    while (i!=6)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        main.Draw(textID);
        i = main.checkButtonMenu(textID);
        if(i==0)
        {
            Game play(main.l, main.scr);
            play.Run(textID);
            main.l = play.GetLevel();
            main.scr = play.GetScore();
        }
        if (i==1)
        {
            int level = main.Level(main.l, textID);
            if (level!=0)
            {
                main.l = level;
                Game play(main.l, main.scr);
                play.Run(textID);
                main.l = play.GetLevel();
                main.scr = play.GetScore();
            }
        }
        if (i==3)
        {
            Tutorial t;
            t.Run(textID);
        }
        FsSwapBuffers();
        FsSleep(25);
    }
    return 0;
}