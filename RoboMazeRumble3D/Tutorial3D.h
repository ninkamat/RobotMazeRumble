#ifndef TUTORIAL_H_IS_INCLUDED
#define TUTORIAL_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Robotclass3D.h"
#include "Menu3D.h"
#include "maze3D.h"

class Tutorial
{
protected:
	int i, counter;

public:
	Tutorial();
	~Tutorial();
	bool CheckCondition(int i,HumanRobot &h, GLuint textID[]);
	void DisplayInstructions(int i);
	void Congratulations(void);
	void Run(GLuint textID[]);
};

#endif