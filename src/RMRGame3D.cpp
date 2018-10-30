//
//  RMRGame3D.cpp
//  RoboMazeRumble3D
//
//  Created by Ninad Kamat on 11/20/15.
//  Copyright © 2015 2b||!2b. All rights reserved.
//

#include "RMRGame3D.h"
#include "EndOfLevel.h"




Game::Game(int level, int score)
{
	this->level = level;
	this->score = score;
	printf("Level: %d; Score: %d\n",level,score);
	TargetReached = false;
}

int Game::EndLevel(GLuint textID [])
{
	//State 0 - Run Next Level
	//State 1 - Restart Current Level
	//State 2 - Go to MainMenu
	OBJData stl;
	stl.ReadObj("crown.obj");

	OBJData bot;
	bot.ReadObj("2bot.obj");

	OrbitViewer camera;

	camera.dist=400.0;

	camera.farZ=600.0;

	stl.Move(0.0,40.0,0.0);

	Confetti celebrate[100];							//Initialize the celebration
	for(auto &i : celebrate)
	{
		i.Initialize();
	}

	int state = 0;
	bool terminate = false;
	auto fontDispList=glGenLists(256);
	int selWid,selHei;
	YsGlSelectAndUseFontBitmapByHeight(&selWid,&selHei,fontDispList,40);

	int winner = 3;

	int prevWid,prevHei;
	FsGetWindowSize(prevWid,prevHei);

	while (terminate == false)
	{
		int wid,hei;
		FsGetWindowSize(wid,hei);

		stl.Rotate(1.0,0.0,1.0,0.0);
		bot.Rotate(1.0,0.0,1.0,0.0);

		if(wid!=prevWid || hei!=prevHei)
		{
			YsGlSelectAndUseFontBitmapByHeight(&selWid,&selHei,fontDispList,hei/20);
			prevWid=wid;
			prevHei=hei;
		}

		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,wid,hei);

		// Set up 3D drawing
		camera.UpdateCameraPosition();
		camera.SetUpCameraProjection();
		camera.SetUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1,1);

		// 3D drawing from here
		bot.Draw(winner);
		stl.Draw(winner);

		// Set up 2D drawing
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//glColor3ub(0, 0, 255);
		//glVertex2i(0,0);
		//glVertex2i(675,0);
		//glVertex2i(675,675);
		//glVertex2i(0,675);
		//DrawBck(textID);
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4ub(135, 206, 250,100);
		glBegin(GL_QUADS);
		if (level<=4 || TargetReached!=true)
		{
			//Next Level
			glVertex2d(0.3*(double)wid,0.6*(double)hei);
			glVertex2d(0.3*(double)wid,0.7*(double)hei);
			glVertex2d(0.7*(double)wid,0.7*(double)hei);
			glVertex2d(0.7*(double)wid,0.6*(double)hei);
		}

		//Go To Main
		glVertex2d(0.3*(double)wid,0.8*(double)hei);
		glVertex2d(0.3*(double)wid,0.9*(double)hei);
		glVertex2d(0.7*(double)wid,0.9*(double)hei);
		glVertex2d(0.7*(double)wid,0.8*(double)hei);

		glEnd();
		glDisable(GL_BLEND);

		if (TargetReached)
		{
			winner = 0;
			//Next Level
			glColor3ub(255,0,0);
			glRasterPos2d((double)wid*0.5-(double)selWid*4, 0.1*(double)hei+(double)selHei/2.);
			glListBase(fontDispList);
			glCallLists(8,GL_UNSIGNED_BYTE,"YOU WON!");


			for(auto &i : celebrate)						//Draw the confetti
			{
				i.DrawConfetti();
			}

			//YsGlDrawFontBitmap24x40("YOU WON!");
			if(level <= 4)
			{
				glColor3ub(0,0,250);
				glRasterPos2i((double)wid*0.5-5*(double)selWid, 0.65*(double)hei+(double)selHei/2.);
				glListBase(fontDispList);
				glCallLists(10,GL_UNSIGNED_BYTE,"NEXT LEVEL");

				//YsGlDrawFontBitmap24x40("NEXT LEVEL");
			}
		}
		else
		{
			winner = 1;
			//Restart
			glColor3ub(255,0,0);
			glRasterPos2i(0.5*(double)wid-(double)selWid*4.5, 0.1*(double)hei+(double)selHei/2.);
			glListBase(fontDispList);
			glCallLists(9,GL_UNSIGNED_BYTE,"YOU LOSE!");
			//YsGlDrawFontBitmap24x40("YOU LOSE!");
			glColor3ub(0,0,250);
			glRasterPos2d(0.5*(double)wid-(double)selWid*3.5, 0.65*(double)hei+(double)selHei/2.);
			glListBase(fontDispList);
			glCallLists(7,GL_UNSIGNED_BYTE,"RESTART");
			//YsGlDrawFontBitmap24x40("RESTART");
		}
		//Go To Main
		glColor3ub(0,0,250);
		glRasterPos2d(0.5*(double)wid-(double)selWid*5, 0.85*(double)hei+(double)selHei/2.);
		glListBase(fontDispList);
		glCallLists(10,GL_UNSIGNED_BYTE,"GO TO MENU");
		//YsGlDrawFontBitmap24x40("GO TO MENU");
		int lb, mb, rb, mx, my;
		FsGetMouseEvent(lb, mb, rb, mx, my);
		if (lb == FSMOUSEEVENT_LBUTTONDOWN)
		{
			if (0.3*(double)wid<=mx && mx<=0.7*(double)wid && 0.6*(double)hei<=my && my<=0.7*(double)hei && (TargetReached!=true||level<=4))
			{
				state = TargetReached==true?0:1;
				terminate = true;
				//printf("Clicked Button 1\n");
			}
			if (0.3*(double)wid<=mx && mx<=0.7*(double)wid && 0.8*(double)hei<=my && my<=0.9*(double)hei)
			{
				state = 2;
				terminate = true;
				//printf("Clicked Button 2\n");
			}
		}

		FsSwapBuffers();
		FsSleep(25);
	}
	return state;
}

int Game::GetScore()
{
	return score;
}

int Game::GetLevel()
{
	return level;
}

bool Game::Run(GLuint textID [])
{
	int state;
	bool terminate = false;
	do
	{
		int result = OneLevel(textID);
		if (result%3 == 0)
		{
			TargetReached = result==3?true:false;
			if (TargetReached == true)
			{
				score+=(100 + 20*(level-1));
				level++;
			}
			state = EndLevel(textID);
			if (level>4)
				level = 4;
			if (state == 2)
			{
				terminate = true;
			}

		}
		else
		{
			if (result == 2)
				terminate = true;
		}
		//printf("Score is %d\n",score);
		//printf("Level is %d\n",level);
	}
	while (terminate == false && level!=5);
	return TargetReached;
}

int Game::OneLevel(GLuint textID [])
{
	//returnstate 0 - Lost
	//returnstate 1 - Restart
	//returnstate 2 - Aborted
	//returnstate 3 - Won
    srand((int)time(NULL));
    int n = 7;
	int speed = 40;
	int returnstate = 0;
	switch (level)
	{
	case 1:
		n = 7;
		break;
	case 2:
		n = 12;
		speed = 30;
		break;
	case 3:
		n = 22;
		speed = 25;
		break;
	case 4:
		n = 37;
		speed = 20;
		break;
	}
	Maze m(n);
	Astar champ;
	m.GenerateMaze(champ);
	ComputerRobot c(m.GetDimension());
	c.path = champ.GetPath();
	HumanRobot h(m.GetDimension(),m.GetPointer());
	Pause p;
	bool terminate = false;
	GLuint txt[3];
	m.TextureMapping(txt);


	int cycle = 0;
	FsClearEventQueue();
	while (terminate != true)
	{
		FsPollDevice();

		int wid,hei;
		FsGetWindowSize(wid,hei);

		auto key = FsInkey();
		if (key == FSKEY_ESC)
		{
			switch (p.Draw(textID))
			{
			case 1:
				returnstate = 1;
				terminate = true;
				break;
			case 2:
				returnstate = 2;
				terminate = true;
				break;
			}
		}

		h.Move(key);
		cycle++;
		if (cycle%speed==0)
			c.Move();
		auto win = h.CheckTarget();
		if(win==true||c.CheckTarget()==true)
		{
			returnstate = win==true?3:0;
			terminate = true;
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
		m.Draw3D(txt);

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		m.Draw2d();
		h.Draw();
		c.Draw();
		// 2D drawing from here

		FsSwapBuffers();
		FsSleep(10);

	}
	return returnstate;
}
