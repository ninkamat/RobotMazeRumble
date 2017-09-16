#include "Tutorial3D.h"
#include "EndofLevel.h"

Tutorial :: Tutorial()
{
	i=0;
	counter=0;
}

Tutorial :: ~Tutorial()
{
	i=0;
	counter=0;
}

bool Tutorial::CheckCondition(int i,HumanRobot &h, GLuint textID[])
{
	FsPollDevice();

	int key = FsInkey();

	switch (i)
	{
	case 0:
		if (FSKEY_UP == key)
		{
			++counter;
			//h.Move(key);
		}
		break;
	case 1:
		if (FSKEY_DOWN == key)
		{
			++counter;
			//h.Move(key);
		}
		break;
	case 2:
		if (FSKEY_UP == key || FSKEY_DOWN == key)
		{
			//if(FsGetKeyState(FSKEY_UP) != 0)
			//{
			//h.Move(key);
			//}
		}
		if (FSKEY_RIGHT == key || FSKEY_LEFT == key)
		{
			//if(FsGetKeyState(FSKEY_UP) != 0)
			//{
			++counter;
			//h.Move(key);
			//}
		}
		break;

	case 3:
		if (FSKEY_ESC == key)
		{
			Pause p;
			int a = p.Draw(textID);
			switch (a)
			{
			case 0:
				//cout << "\nResume";
				counter = 20;
				break;
			case 1:
				counter = 20;
				//cout << "\nRestart";
				break;
			case 2:
				counter = 30;
				//cout << "\nGo to menu";
				break;
			}
		}
		break;
	case 4:
		if (FSKEY_UP == key || FSKEY_DOWN == key || FSKEY_RIGHT == key || FSKEY_LEFT == key)
		{
			//h.Move(key);
			if (h.CheckTarget() == true)
			{
				counter = 20;
				//REPLACE WITH END OF MAZE CHECK
			}
			break;
		}
		break;

	default: //case 5
		Congratulations();
		break;
	}

	if (counter == 20)
	{
		counter = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Tutorial::DisplayInstructions(int i)
{
    int wid, hei;
    FsGetWindowSize(wid, hei);
    switch (i)
	{
	case 0:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0, 0, 0, 0.5);
		glBegin(GL_QUADS);
		glVertex2i(0, 0.16*hei);
		glVertex2i(0, 0);
		glVertex2i(wid, 0);
		glVertex2i(wid, 0.16*hei);
		glDisable(GL_BLEND);
		glEnd();
		glColor3d(255, 255, 255);
		glRasterPos2i(0.5*wid-27*8, 0.08*hei+12);
		YsGlDrawFontBitmap16x24("Press [UP] to move upwards!");
		break;
	case 1:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0, 0, 0, 0.5);
		glBegin(GL_QUADS);
        glVertex2i(0, 0.16*hei);
        glVertex2i(0, 0);
        glVertex2i(wid, 0);
        glVertex2i(wid, 0.16*hei);
        glDisable(GL_BLEND);
		glEnd();
		glColor3d(255, 255, 255);
        glRasterPos2i(0.5*wid-31*8, 0.08*hei+12);
        YsGlDrawFontBitmap16x24("Press [DOWN] to move backwards!");
		break;
	case 2:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0, 0, 0, 0.5);
		glBegin(GL_QUADS);
        glVertex2i(0, 0.16*hei);
        glVertex2i(0, 0);
        glVertex2i(wid, 0);
        glVertex2i(wid, 0.16*hei);
        glDisable(GL_BLEND);
		glEnd();
		glColor3d(255, 255, 255);
        glRasterPos2i(0.5*wid-32*8, 0.08*hei+12);
        YsGlDrawFontBitmap16x24("Press [LEFT] or [RIGHT] to turn!");
		break;
	case 3:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0, 0, 0, 0.5);
		glBegin(GL_QUADS);
        glVertex2i(0, 0.16*hei);
        glVertex2i(0, 0);
        glVertex2i(wid, 0);
        glVertex2i(wid, 0.16*hei);
        glDisable(GL_BLEND);
		glEnd();
		glColor3d(255, 255, 255);
        glRasterPos2i(0.5*wid-30*8, 0.08*hei+12);
        YsGlDrawFontBitmap16x24("Press [ESC] to pause the game!");
		break;
	case 4:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0, 0, 0, 0.5);
		glBegin(GL_QUADS);
        glVertex2i(0, 0.16*hei);
        glVertex2i(0, 0);
        glVertex2i(wid, 0);
        glVertex2i(wid, 0.16*hei);
        glDisable(GL_BLEND);
		glEnd();
		glColor3d(255, 255, 255);
        glRasterPos2i(0.5*wid-31*8, 0.08*hei+12);
        YsGlDrawFontBitmap16x24("Now get to the end of the maze!");
		break;
	default: //case 5
		Congratulations();
		break;
	}
}

void Tutorial::Congratulations(void)
{
	//int count = 0;
	Confetti celebrate[100];							//Initialize the celebration
	for(auto &i : celebrate)
	{
		i.Initialize();
	}
	while(counter == 0)									//Remain in this loop
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//camera.UpdateCameraPosition();
		//camera.SetUpCameraProjection();
		//camera.SetUpCameraTransformation();

		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_POLYGON_OFFSET_FILL);
		//glPolygonOffset(1,1);
        int wid,hei;
        FsGetWindowSize(wid,hei);
        
		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		glColor3d(0,0,255);
		glRasterPos2i(350,150);
		YsGlDrawFontBitmap28x44("You've got it now!");	//Display a celebratory message
		glRasterPos2i(300,250);
		YsGlDrawFontBitmap28x44("You're ready to play!");
		glRasterPos2i(420,470);
		YsGlDrawFontBitmap28x44("Press [Enter]");
		glRasterPos2i(300,550);
		YsGlDrawFontBitmap28x44("to return to the menu.");
		glColor3d(255,0,0);
		glRasterPos2i(180,120);

		for(auto &i : celebrate)						//Draw the confetti
		{
			i.DrawConfetti();
		}

		FsSwapBuffers();							//Swap the buffers so the animation can run
		FsSleep(25);								//Wait a bit

		FsPollDevice();

		int key=FsInkey();

		if(FSKEY_ENTER==key)
		{
			counter = 30;
		}
	}
}

void Tutorial :: Run(GLuint textID[])
{
	//Start();
    int n = 7;
    Maze m(n);
    Astar champ;
    m.GenerateMaze(champ);
    HumanRobot h(m.GetDimension(),m.GetPointer());
    //Pause p;
    bool terminate = false;
    GLuint txt[3];
    m.TextureMapping(txt);
    FsClearEventQueue();
    for(int i=0; i<=5; i++)
    {
        while(CheckCondition(i,h, textID) != true && terminate != true)
        {
            FsPollDevice();
            
            int wid,hei;
            FsGetWindowSize(wid,hei);
            
            auto key = FsInkey();
            /*if (key == FSKEY_ESC)
            {
                switch (p.Draw())
                {
                    case 1:
                        terminate = true;
                        break;
                    case 2:
                        terminate = true;
                        break;
                }
            }*/
			if (counter == 30)
			{
				terminate = true;
			}

            h.Move(key);
            
            glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
            
            glViewport(0,0,wid,hei);
            
            // Set up 3D drawing
            h.SetUpCameraProjection();
            h.SetUpCameraTransformation();
            
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1,1);
            
            // 3D drawing from here
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
            DisplayInstructions(i);
            
            // 2D drawing from here
            
            FsSwapBuffers();
            FsSleep(10);
			if (i == 5)
			{
				terminate = true;
			}
        }
        
    }

}
