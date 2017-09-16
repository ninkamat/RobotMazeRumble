
#include "Menu3D.h"



//////////////////////////////////////////////////////////////////////////////////////////////////
//General Functions 
//
//These functions are used my members of all the classes 
//These have been kept public , since there is going to be no data that is going to be modified by these fucntions.
//They are purely built for the purpose of graphics
//pasing and getting words
//////////////////////////////////////////////////////////////////////////////////////////////////
int Parse(int wordTop[], int wordLength[], int maxNumWord, char str[])
{
	int state = 0;  // 0:Blank   1:Visible Letter
	int nw = 0;
	for (int i = 0; 0 != str[i]; ++i)
	{
		switch (state)
		{
		case 0:
			if (' ' != str[i] && isprint(str[i]))
			{
				if (nw<maxNumWord)
				{
					wordTop[nw] = i;
					wordLength[nw] = 1;
				}
				else
				{
					goto LOOPOUT;
				}
				++nw;
				state = 1;
			}
			else
			{
			}
			break;
		case 1:
			if (' ' != str[i] && isprint(str[i]))
			{
				wordLength[nw - 1]++;
			}
			else
			{
				state = 0;
			}
			break;
		}
	}
LOOPOUT:

	return nw;
}

void GetWord(char wd[], char str[], int wordTop, int wordLength, int bufSize)
{
	int l = wordLength;
	if (bufSize<l)
	{
		l = bufSize;
	}
	strncpy(wd, str + wordTop, l);
	wd[l] = 0;
}


//Checks if the Pofile is in the File 
int checkinFile(const char str[])
{
	int i = 0;
	FILE *fp;
	fp = fopen("profilesold.txt", "r");
	int wordTop[5], wordLength[5];
	if (nullptr != fp)
	{
		char check[256];
		int ctr = 0;
		while (nullptr != fgets(check, 255, fp))
		{
			int nw = Parse(wordTop, wordLength, 5, check);
			if (nw > 0 && ctr != 0)
			{
				char wd[256];
				GetWord(wd, check, wordTop[1], wordLength[1], 255);
				if (0 == strcmp(wd, str))
				{
					i = 1;
				}
			}
			ctr++;
		}
		fclose(fp);
	}
	else
	{
		printf("File not found Found \n");
	}
	return i;
}
//Sorts the LeaderBoard in Desceiding order
void sortLeader(int &n, Player Players[], char Name[], int l, int score)
{
    n = n - 1;
    int exist = 0;
    for (int i = 0; i < n; i++)
    {
        //printf("It comes here to check if already exist \n");
        if (0 == strcmp(Name, Players[i].Name))
        {
            Players[i].scr = score;
            Players[i].l = l;
            exist = 1;
        }
        
    }
    if (exist == 0)
    {
        if (n<5)
        {
            //printf("It comes here to check if less than min\n");
            //printf("Member number %d", n);
            strcpy(Players[n].Name, Name);
            Players[n].l = l;
            Players[n].scr = score;
            n = n + 1;
        }
        else
        {
            if (score>Players[n - 1].scr)
            {
                //printf("It comes here to check if never seen before \n");
                strcpy(Players[n - 1].Name, Name);
                Players[n - 1].l = l;
                Players[n - 1].scr = score;
            }
            
        }
    }
    for (int i = 0; i<n; ++i)
    {
        //printf("It comes for sorting \n");
        for (int j = i + 1; j<n; ++j)
        {
            if (Players[j].scr>Players[i].scr)
            {
                Player Dummy;
                strcpy(Dummy.Name, Players[j].Name);
                strcpy(Players[j].Name, Players[i].Name);
                strcpy(Players[i].Name, Dummy.Name);
                Dummy.scr = Players[j].scr;
                Players[j].scr = Players[i].scr;
                Players[i].scr = Dummy.scr;
                Dummy.l = Players[j].l;
                Players[j].l = Players[i].l;
                Players[i].l = Dummy.l;
            }
        }
    }
}

//Update Profile:
void ProfileUpdate(FILE *fpo, FILE *fpi)
{
	fpo = fopen("profilesold.txt", "w");
	fpi = fopen("profilesnew.txt", "r");
	if (nullptr != fpi && nullptr != fpo)
	{
		char check[256];
		while (nullptr != fgets(check, 255, fpi))
		{
			fprintf(fpo, "%s", check);
		}
		fclose(fpo);
		fclose(fpi);
	}
	else
	{
		printf("File not found Found \n");
	}
}
//Update the Scoreboard
void ScoreBoardUpdate(FILE *fpo, FILE *fpi)
{
	fpo = fopen("scorecardold.txt", "w");
	fpi = fopen("scorecardnew.txt", "r");
	if (nullptr != fpi && nullptr != fpo)
	{
		char check[256];
		while (nullptr != fgets(check, 255, fpi))
		{
			fprintf(fpo, "%s", check);
		}
		fclose(fpo);
		fclose(fpi);
	}
	else
	{
		printf("File not found Found \n");
	}
}
//Initilise the Viweing port 
void Initialise()
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}



// Draws the Font of the Desired format 
void DrawTextDesiredSize(int X, int Y,int wid ,int hei,const char str[])
{
	auto fontDispList = glGenLists(256);
	int selHeight, selWidth, width, height;
	FsGetWindowSize(width, height);
	YsGlSelectAndUseFontBitmapByHeight(&selWidth, &selHeight, fontDispList, height / 35);
	glRasterPos2d(X+wid/2-strlen(str)/2*selWidth, Y+hei/2+selHeight/2);
	glListBase(fontDispList);
	glCallLists((int)strlen(str), GL_UNSIGNED_BYTE, str);
    for(int i = 0; i<256; i++)
        glDeleteLists(fontDispList+i, 1);
}


//Conversion from Number to stpring 
void Num2Str(char str[], int num)
{
	int newnum = num;
	char strtemp[256];
	int loc = 0;
	do
	{
		switch (newnum % 10)
		{
		case 0:
			strtemp[loc] = '0';
			break;
		case 1:
			strtemp[loc] = '1';
			break;
		case 2:
			strtemp[loc] = '2';
			break;
		case 3:
			strtemp[loc] = '3';
			break;
		case 4:
			strtemp[loc] = '4';
			break;
		case 5:
			strtemp[loc] = '5';
			break;
		case 6:
			strtemp[loc] = '6';
			break;
		case 7:
			strtemp[loc] = '7';
			break;
		case 8:
			strtemp[loc] = '8';
			break;
		case 9:
			strtemp[loc] = '9';
			break;
		}
		loc++;
		newnum = newnum / 10;
	} while (newnum>0);
	strtemp[loc] = 0;
	for (int i = 0; i < strlen(strtemp)+1; i++)
	{
		str[i] = strtemp[strlen(strtemp) - 1 - i];
	}
	str[loc] = 0;
}


//Draws The ScoreBoardBackdrop
void DrawScrButton(int x, int y, int width , int height,GLuint textID[])
{
	Initialise();
	glColor3ub(255, 255, 255);
	int posX;
	for (int c = 0; c < 6; c++)
	{
		posX = x;
		for (int d = 0; d < 4; d++)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textID[2]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0, 0.0);
			glVertex2i(posX, y);
			glTexCoord2d(1.0, 0.0);
			glVertex2i(posX + width, y);
			glTexCoord2d(1.0, 1.0);
			glVertex2i(posX + width, y + height);
			glTexCoord2d(0.0, 1.0);
			glVertex2i(posX, y + height);
			glEnd();
			posX = posX + 150;
		}
		y = y + 50;
	}
}
//Draws the Backdrop of the load and Save Function
void DrawLSButton(int x, int y, int width, int height,GLuint textID[])
{
	Initialise();
	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2i(x ,y);
	glTexCoord2d(1.0, 0.0);
	glVertex2i(x + width, y);
	glTexCoord2d(1.0, 1.0);
	glVertex2i(x + width, y + height);
	glTexCoord2d(0.0, 1.0);
	glVertex2i(x, y + height);
	glEnd();
}
//Draws the user Instruction for load and Save
void DisplayLS(const char str[], const int i,GLuint textID[])
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	DrawLSButton(0.125*wid, 0.25*hei, 0.75*wid, 100,textID);
	glColor3ub(0, 0, 0);
	glRasterPos2d(100, 200);
	switch (i)
	{
	case 2:
		//YsGlDrawFontBitmap20x32("Enter Profile To Save:");
		DrawTextDesiredSize(0.125*wid, 0.25*hei, 0.75*wid, 100,"Enter Profile To Save: ");
		break;
	case 5:
		DrawTextDesiredSize(0.125*wid, 0.25*hei, 0.75*wid, 100, "Enter Profile To Load: ");
		//YsGlDrawFontBitmap20x32("Enter Profile To Load:");
		break;
	}
	//glRasterPos2d(100, 300);
	//YsGlDrawFontBitmap20x32(str);
	DrawTextDesiredSize(0.125*wid, 0.5*hei, 0.75*wid, 100,str);
	//glRasterPos2d(100, 550);
	//YsGlDrawFontBitmap20x32("Press ESC To Go Back");
	DrawTextDesiredSize(0.125*wid, 0.75*hei, 0.75*wid, 100, "Press ESC To Go Back");
}
//Draws the Text Limit Error
void DrawErrLS(void)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	DrawTextDesiredSize(wid*0.125, hei/2, wid*0.8, 50, "Name Should be 6 characters");
	FsSwapBuffers();
	int  seconds = 2;
	time_t currentTime = time(NULL);											/*time_t is the default type for time()*/
	while (seconds>0)
	{
		time_t endTime = time(NULL);
		if ((endTime - currentTime) == 1)
		{

			currentTime = endTime;
			seconds--;
		}
	}
}


//Draws the Profile Error Message
void DrawErrLS2(const int i)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	switch (i)
	{
	case 2:
		DrawTextDesiredSize(wid *0.125, hei / 2, wid*0.8, 50, "Profile name Already Exists");
		break;
	case 5:
		DrawTextDesiredSize(wid *0.125, hei / 2, wid*0.8, 50, "Profile Name Not Found");
		break;
	}
	
	FsSwapBuffers();
	int  seconds = 2;
	time_t currentTime = time(NULL);											/*time_t is the default type for time()*/
	while (seconds>0)
	{
		time_t endTime = time(NULL);
		if ((endTime - currentTime) == 1)
		{

			currentTime = endTime;
			seconds--;
		}
	}
}
//Displays the profile Details 
void Display(char Name[], int l, int scr, int StartX, int StartY, int w, int h)
{
	glColor3ub(250, 0, 0);
	char display[256];
	strcpy(display, "Player:");
	strcat(display, Name);
	//glRasterPos2d(StartX, StartY - 10);
	//YsGlDrawFontBitmap16x20(display);
	DrawTextDesiredSize(StartX, StartY,w,h, display);
	char scoredis[5];
	strcpy(display, "Level:");
	Num2Str(scoredis, l);
	strcat(display, scoredis);
	//glRasterPos2d(StartX, StartY - 10);
	//YsGlDrawFontBitmap16x20(display);
	DrawTextDesiredSize(StartX*7, StartY,w,h ,display);
	strcpy(display, "Score:");
	Num2Str(scoredis, scr);
	strcat(display, scoredis);
	//glRasterPos2d(StartX, StartY - 10);
	//YsGlDrawFontBitmap16x20(display);
	DrawTextDesiredSize(StartX*11, StartY,w,h, display);
}
//Function Draws the Background
extern void DrawBck(GLuint textID[])
{
	Initialise();
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID[0]);
	glColor4d(1.0,1.0,1.0,1.0);
    glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex2i(wid, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex2i(wid, hei);
	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, hei);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Draw The Title

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textID[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex2i(wid, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex2i(wid, hei / 5);
	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, hei / 5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
// Function Draws the Menu Objects
void DrawRectangle(int x, int y, int w, int h)
{
	glColor3ub(135, 206, 250);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
}

// If font size is changed the position of the letter will also change
//Function Draws the letters on the Menu
void DrawLettersMenu(int x, int y, int w, int h, int i)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glColor3ub(0, 0, 250);
	switch (i)
	{
	case 0:
		//glRasterPos2d((x + w / 2) - 2 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("START");
		DrawTextDesiredSize(x,y,w,h, "START");
		break;
	case 1:
		//glRasterPos2d((x + w / 2) - 2.5 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LEVEL");
		DrawTextDesiredSize(x, y, w, h, "LEVEL");
		break;
	case 2:
		//glRasterPos2d((x + w / 2) - 2 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("SAVE");
		DrawTextDesiredSize(x, y, w, h, "SAVE");
		break;
	case 3:
		//glRasterPos2d((x + w / 2) - 4 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("TUTORIAL");
		DrawTextDesiredSize(x, y, w, h, "TUTORIAL");
		break;
	case 4:
		//glRasterPos2d((x + w / 2) - 5 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("SCOREBOARD");
		DrawTextDesiredSize(x, y, w, h, "SCOREBOARD");
		break;
	case 5:
		//glRasterPos2d((x + w / 2) - 2 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LOAD");
		DrawTextDesiredSize(x, y, w, h, "LOAD");
		break;
	case 6:
		//glRasterPos2d((x + w / 2) - 2 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("EXIT");
		DrawTextDesiredSize(x, y, w, h, "EXIT");
		break;
		break;
	default:
		break;
	}
}
void DrawLettersLevel(int x, int y, int w, int h, int i)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glColor3ub(0, 0, 250);

	switch (i)
	{
	case 0:
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LEVEL1");
		DrawTextDesiredSize(x, y, w, h, "LEVEL1");
		break;
	case 1:
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LEVEL2");
		DrawTextDesiredSize(x, y, w, h, "LEVEL2");
        break;
	case 2:
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LEVEL3");
		DrawTextDesiredSize(x, y, w, h, "LEVEL3");
		break;
	case 3:
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("LEVEL4");
		DrawTextDesiredSize(x, y, w, h, "LEVEL4");
		break;
	}
}
void DrawLettersPause(int x, int y, int w, int h, int i)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	glColor3ub(0, 0, 250);
	switch (i)
	{
	case 0:
		DrawTextDesiredSize(x,y,w,h,"RESUME");
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("RESUME");
		break;
	case 1:
		//glRasterPos2d((x + w / 2) - 3 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("RESTART");
		DrawTextDesiredSize(x, y, w, h, "RESTART");
		break;
	case 2:
		//glRasterPos2d((x + w / 2) - 5 * 16, (y + h / 2) + 10);
		//YsGlDrawFontBitmap16x20("GO TO MENU");
		DrawTextDesiredSize(x, y, w, h, "GO TO MENU");
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//Menu Definitions are included here
/////////////////////////////////////////////////////////////////////////////////////////
Menu::Menu()
{
	strcpy(Name, "Guest");
	l = 1;
	scr = 0;

}

Menu::~Menu()
{
}
void Menu::Calculate()
{
	FsGetWindowSize(windowWidth, windowHeight);
	width = int(windowWidth / 4);
	section = int(0.75*windowHeight / 8);
	height = int(section*0.8);
	startY = int(0.25*windowHeight);
}

void Menu::Draw(GLuint textID[])
{
	Calculate();
	glColor3ub(255, 255, 255);
	DrawBck(textID);
	startX = int(width / 4);
	for (int i = 0; i < 7; i++)
	{
			DrawRectangle(startX, startY + i*(section), width, height);
			DrawLettersMenu(startX, startY + i*(section), width, height, i);
	}

	Display(Name, l, scr, startX, startY*4/5, width,height*0.8);


}

int Menu::Level(int l, GLuint textID[])
{
	for (;;)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		Draw(textID);
		startX = int(width / 2 + width);
		for (int i = 0; i < l; i++)
		{
				DrawRectangle(startX, startY + i*(section), width, height);
				DrawLettersLevel(startX, startY + i*(section), width, height, i);
		}
		FsPollDevice();
        int button = checkButtonLevel(l);
        if (button == 7)
        {
            break;
        }
        if (button >= 0 && button <= 6)
        {
            return button;
        }
        FsSwapBuffers();
        FsSleep(25);
    }
    //FsSleep(500);
    return 0;
}

int Menu::checkButtonMenu(GLuint textID[])
{
	mx = 0;
	my = 0;
	FsGetMouseEvent(lb, mb, rb, mx, my);
	startX = int(width / 4); 
	for (int i = 0; i < 7; i++)
	{
		if (mx>startX && mx<(startX + width) && my>(startY + i*(section)) && my<((startY + i*(section)) + height))
		{
			if (lb == FSMOUSEEVENT_LBUTTONDOWN)
			{
				switch (i)
				{
				case 0:
					//l = 1;
					//play(l);
					//play.Run()
					//scr=play.GetScore();
					//l=play.GetLevel();
					return i;
					break;
				case 1:
					//l = Level(l, textID);
					//l++;
					//play(l);
					//play.Run()
					//scr=play.GetScore();
					//l=play.GetLevel();
					//printf("Button:%d \n", i + 1);
					//printf("Level Selected by user:%d", l);
					return i;
					break;
				case 2:
					Save(2, textID);
					//printf("Button:%d \n", i + 1);
					return i;
					break;
				case 3:
					//printf("Button:%d \n", i + 1);
					return i;
					break;
				case 4:
					ScoreCard(textID);
					//printf("Button:%d \n", i + 1);
					return i;
					break;
				case 5:
					Load(5, textID);
					return i;
					break;
				case 6:
					//printf("Button:%d \n", i + 1);
					return i;
					break;
				default:
					break;
				}
			}
		}
	}
	return 7;
}

int Menu::checkButtonLevel(int l)
{

	mx = 0;
	my = 0;
	int check = 0;
	FsGetMouseEvent(lb, mb, rb, mx, my);
	startX = int(width / 2 + width); 
	if (lb == FSMOUSEEVENT_LBUTTONDOWN)
	{
			for (int i = 0; i < l; i++)
			{

				if (mx>startX && mx<(startX + width) && my>(startY + i*(section)) && my < ((startY + i*(section)) + height))
				{
//					printf("Level:%d \n", i+1);
					check = 1;
					return i+1;
				}
			}
			if (check==0)
			{
//				printf("Not Executed the Level \n");
				return 7;
			}
	}
    return 8;
}

void Menu::ScoreCard(GLuint textID [])
{
	FsPollDevice();
	while (FsInkey() != FSKEY_ESC)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		DrawScrButton(30, 10, 150, 50,textID);
		FILE *fp = fopen("scorecardold.txt", "r");
		int wordTop[5], wordLength[5];
		int nw;
		if (nullptr != fp)
		{
			char str[256];
			int posY = 0;
			while (nullptr != fgets(str, 255, fp))
			{
				nw = Parse(wordTop, wordLength, 5, str);
				if (nw > 0)
				{
					char wd[256];
					for (int i = 0; i < nw; i++)
					{
						GetWord(wd, str, wordTop[i], wordLength[i], 255);
						glColor3ub(0, 0, 0);
						glRasterPos2d(50 + i * 150, 50 * (posY + 1));
						YsGlDrawFontBitmap20x32(wd);
					}
				}
				posY++;
			}
			glRasterPos2d(100, 550);
			YsGlDrawFontBitmap20x32("Press ESC To Go Back");
			fclose(fp);
		}
		else
		{
			printf("File not found \n");
		}
		FsSwapBuffers();
		FsSleep(20);
	}
}
void Menu::Load(const int opt, GLuint textID [])
{
	char str[256];
	str[0] = 0;
	FsPollDevice();
	int state = 0;
	FILE *fp = fopen("profilesold.txt", "r");
	while (state == 0)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			state=1;
			break;
		case FSKEY_ENTER:
				if (strlen(str) == 6)
				{
					int wordTop[5], wordLength[5];
					if (nullptr != fp)
					{
                        bool readstate = true;
                        char check[256];
						while (nullptr != fgets(check, 255, fp))
						{
							int nw = Parse(wordTop, wordLength, 5, check);
							if (nw>0)
							{
									char wd[256];
									GetWord(wd, check, wordTop[1], wordLength[1], 255);
									if (0 == strcmp(wd, str))
									{
                                        readstate = true;
                                        strcpy(Name, wd);
										GetWord(wd, check, wordTop[2], wordLength[2], 255);
										l = atoi(wd);
										GetWord(wd, check, wordTop[3], wordLength[3], 255);
										scr = atoi(wd);
										state = 1;
										fclose(fp);
                                        break;
									}
                                else
                                {
                                    readstate = false;
                                }
                            }
                        }
                        if (readstate == false)
                        {
                            DrawErrLS2(5);
                        }
                    }
                    else
                    {
                        printf("File not found \n");
                    }
                    break;
                }
                else
                {
                    DrawErrLS();
                    break;
                }

		case FSKEY_BS:
		{
						 int l = (int)strlen(str);
						 if (0 < l)
						 {
							 str[l - 1] = 0;
						 }
		}
			break;
		}
		char c = FsInkeyChar();
		if (('A' <= c &&  c <= 'Z') || ('a' <= c &&  c <= 'z'))
		{
			int l = (int)strlen(str);
			if (l < 6 && 0 != isprint(c))
			{
				str[l] = c;
				str[l + 1] = 0;
				//printf(">> %s\n", str);
			}
		}
		DisplayLS(str, opt,textID);
		FsSwapBuffers();
		FsSleep(20);
	}

}

void Menu::Save(const int i, GLuint textID [])
{
	char str[256];
	str[0] = 0;
	int line;
	int mf = 0;
	int ctr = 0;
	FsPollDevice();
	int state = 0;
	FILE *fpi;
	FILE *fpo;
	FILE *fpscri;
	FILE *fpscro;

	int wordTop[5], wordLength[5];
	fpi = fopen("profilesold.txt", "r");
	fpo = fopen("profilesnew.txt", "w");
	if (nullptr != fpi)
	{
		line = 0;
		char check[256];
		while (nullptr != fgets(check, 255, fpi))
		{
			line++;
			int nw = Parse(wordTop, wordLength, 5, check);
			if (nw > 0)
			{
				char wd[256];
				GetWord(wd, check, wordTop[1], wordLength[1], 255);
				if (0 == strcmp(wd, Name))
				{
					mf = 1;
					char number[5];
					Num2Str(number, l);
					for (int i = 0; i < wordLength[2]; i++)
					{
						check[wordTop[2] + i] = number[i];
					}
//					printf("Score:%d \n", scr);
					Num2Str(number, scr);
					for (int i = 0; i < strlen(number); i++)
					{
						check[wordTop[3] + i] = number[i];
					}
//					printf("New Data:%s \n", check);
					if (wordLength[3] != strlen(number))
					{
						strcat(check, "\n");
					}
				}
				fprintf(fpo, "%s", check);
			}
		}
		if (mf == 0)
		{
//			printf("Match Not Found \n");
			while (state == 0)
			{
				FsPollDevice();
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
				glColor3ub(0, 0, 0);
				int key = FsInkey();
				switch (key)
				{
				case FSKEY_ESC:
					state = 1;
					break;
				case FSKEY_BS:
				{
								 int l = (int)strlen(str);
								 if (0 < l)
								 {
									 str[l - 1] = 0;
								 }
				}
					break;
				case FSKEY_ENTER:
				{
									if (strlen(str) == 6)
									{
										if (1==checkinFile(str))
										{
											DrawErrLS2(2);
										}
										else
										{
											strcpy(Name, str);
											fprintf(fpo, "%d\t%s\t%d\t%d", line++, str, l, scr);
											fprintf(fpo, "\n");
											state = 1;
										}	
									}
									else
									{
										DrawErrLS();
									}
				}
					break;
				default:
					break;
				}


				char c = FsInkeyChar();
				if (('A' <= c &&  c <= 'Z') || ('a' <= c &&  c <= 'z'))
				{
					int l = (int)strlen(str);
					if (l < 6 && 0 != isprint(c))
					{
						str[l] = c;
						str[l + 1] = 0;
						//printf(">> %s\n", str);
					}
				}
				DisplayLS(str, i, textID);
				FsSwapBuffers();
				FsSleep(20);
			}
			
		}
		fclose(fpi);
		fclose(fpo);
	}
	else
	{
		printf("File not found Found \n");
	}

    fpscri = fopen("scorecardold.txt", "r");
    fpscro = fopen("scorecardnew.txt", "w");
    if (nullptr != fpi)
    {
        Player Players[5];
        char checkscore[256];
        while (nullptr != fgets(checkscore, 255, fpi))
        {
            int nw = Parse(wordTop, wordLength, 5, checkscore);
            if (nw > 0 && ctr != 0)
            {
                char wd[256];
                GetWord(wd, checkscore, wordTop[1], wordLength[1], 255);
                strcpy(Players[ctr - 1].Name, wd);
                GetWord(wd, checkscore, wordTop[2], wordLength[2], 255);
                Players[ctr - 1].l = atoi(wd);
                GetWord(wd, checkscore, wordTop[3], wordLength[3], 255);
                Players[ctr - 1].scr = atoi(wd);
            }
            else
            {
                fprintf(fpscro, "%s", checkscore);
            }
            ctr++;
        }
        sortLeader(ctr, Players, Name, l, scr);
        for (int i = 0; i < (ctr); i++)
        {
            fprintf(fpo, "%d\t%s\t%d\t%d", i + 1, Players[i].Name, Players[i].l, Players[i].scr);
            fprintf(fpo, "\n");
        }
        fclose(fpscri);
        fclose(fpscro);
    }
	else
	{
		printf("File not found Found \n");
	}
	ProfileUpdate(fpo, fpi);
	ScoreBoardUpdate(fpscri, fpscro);

}
int Pause::Draw(GLuint textID[])
{
	int wei, hei;
	int width, section, height, startX, startY;
	
	for (;;)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glColor3ub(255, 255, 255);
		DrawBck(textID);
		FsGetWindowSize(wei, hei);
		width = int(wei / 4);
		section = int(0.75*hei / 8);
		height = int(section*0.8);
		startX = int(width / 2 + width);
		startY = int(0.25*wei);
		for (int i = 0; i < 3; i++)
		{
			DrawRectangle(startX, startY + i*(section), width, height);
			DrawLettersPause(startX, startY + i*(section), width, height, i);
		}
		FsPollDevice();
		int mx, my, lb, mb, rb;
		mx = 0;
		my = 0;
		FsGetMouseEvent(lb, mb, rb, mx, my);
		if (lb == FSMOUSEEVENT_LBUTTONDOWN)
		{
			if (true)
			{
				for (int i = 0; i < 3; i++)
				{

					if (mx>startX && mx<(startX + width) && my>(startY + i*(section)) && my < ((startY + i*(section)) + height))
					{
						return i;
					}
				}
			}
		}
		FsSwapBuffers();
	}
}

void Menu::LoadTextures(GLuint textID [])
{
	YsRawPngDecoder png[5];
	png[0].Decode("1.png");
	png[1].Decode("header.png");
	png[2].Decode("scorecard3.png");
	png[3].Decode("scorecard.png");
	png[4].Decode("1.png");
	//png[0].Decode(fn1);
	
	for (int i = 0; i < 5; i++)
	{
		glGenTextures(1, &textID[i]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D, textID[i]);  // Making the texture identifier current (or bring it to the deck)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D
			(GL_TEXTURE_2D,
			0,    // Level of detail
			GL_RGBA,
			png[i].wid,
			png[i].hei,
			0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			png[i].rgba);

	}
}