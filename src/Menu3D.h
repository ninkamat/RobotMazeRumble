
#ifndef MENU_H_IS_INCLUDED
#define MENU_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//The Menu class is the first interface between the user and the game 
//the user has been provided with 6 options
//1. Start : The game strats from the very beginning 
//2. Level: based on the level of the user , the options are provided , so initally the user can see only 1 level 
//3. Save: this tab is used to save the profile of the user 
//4. Tutorial : Helps the user to view the tutorial 
//5. Scoreboard : Helps the user to see the top scorer of the game
//6. Load : Loads the profile of an existing player
//7. Exit : Ends the entire game 
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void DrawBck(GLuint textID[]);

class Menu
{
public:
	//Game play;
	int windowWidth;
	int windowHeight;
	int width, section, height, startX, startY;
	int l;
	char Name[7];
	int scr;
	int mx, my, lb, mb, rb;
	int selWidth, selHeight;


	Menu();
	~Menu();

	void Draw(GLuint textID[]);
	int Level(int l, GLuint textID[]);
	int checkButtonMenu(GLuint textID[]);
	int checkButtonLevel(int level);
	void Calculate();
	void LoadTextures(GLuint textID[]);




	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//The purose of the scorecard class is to the read a file wher the scores of the highest scores have been saved.
	//This is mainly used when the user presses the scorecard button , the list of highest scorers are displayed
	//The user cannot modify anything here 
	//So this is used only to view the table
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ScoreCard(GLuint textID[]);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//The user might want to play a game that he has already played 
	//In such a case a player can retieve the already saved game 
	//This is done with the help of load 
	//This helps to load the Name , the score and the level of the player
	//Based on what is laoded the level otpions become available 
	//thus a player can play any game lower that what he has played but cannot play anything above him 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Load(const int i, GLuint textID[]);

	void Save(const int i, GLuint textID[]);
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////
//The Purpose of the pasue class is to interrupt in the functioning of a game that is being played 
//This class is always called When the user presses the ESC Button
//The Pasue Menu has 3 Options 
//0. Resume: To Begin with the game 
//1. Restart: To start the level from the beginning 
//2. Go To Menu: Nothing will be saved , directly going to the main menu
//
//the sr number of the options indicates the value that shall be return by an object of this class
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Players classs is used to sort all the Players to get the display fot the scoreboard
///////////////////////////////////////////////////////////////////////////////////////////////////////

class Player
{
public:
	char Name[256];
	int l;
	int scr;

};

class Pause
{
public:
	int Draw(GLuint textID[]);
};

#endif