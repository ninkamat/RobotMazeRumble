/* ////////////////////////////////////////////////////////////

File Name: fssimplewindowios_cpp.cpp
Copyright (c) 2015 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include "../fssimplewindow.h"
#include "fssimplewindowios.h"
#include <stdio.h>

class FsMouseEventLog
{
public:
	int eventType,lb,mb,rb,mx,my;
};

// Mouse Emulation
#define NEVTBUF 256
static int nMosBufUsed=0;
static FsMouseEventLog mosBuffer[NEVTBUF];
static FsMouseEventLog lastKnownMos;
static FsVec2i touchCache[NEVTBUF];

static int exposure=0;

static int winWid=0,winHei=0;


extern "C" void FsIOSReportWindowSize(int wid,int hei)
{
	winWid=wid;
	winHei=hei;
}



void FsOpenWindow(const FsOpenWindowOption &)
{
}

void FsCloseWindow(void)
{
}

void FsMaximizeWindow(void)
{
}
void FsUnmaximizeWindow(void)
{
}
void FsMakeFullScreen(void)
{
}

void FsGetWindowSize(int &wid,int &hei)
{
	wid=winWid;
	hei=winHei;
}

void FsGetWindowPosition(int &x0,int &y0)
{
	x0=0;
	y0=0;
}

void FsSetWindowTitle(const char [])
{
}

void FsPushOnPaintEvent(void)
{
}

void FsPollDevice(void)
{
}

void FsSleep(int ms)
{
	FsSleepC(ms);
}

long long int FsSubSecondTimer(void)
{
	return FsSubSecondTimerC();
}

long long int FsPassedTime(void)
{
	return FsPassedTimeC();
}

void FsGetMouseState(int &lb,int &mb,int &rb,int &mx,int &my)
{
	lb=lastKnownMos.lb;
	mb=lastKnownMos.mb;
	rb=lastKnownMos.rb;
	mx=lastKnownMos.mx;
	my=lastKnownMos.my;
}

int FsGetMouseEvent(int &lb,int &mb,int &rb,int &mx,int &my)
{
	if(0<nMosBufUsed)
	{
		const int eventType=mosBuffer[0].eventType;
		lb=mosBuffer[0].lb;
		mb=mosBuffer[0].mb;
		rb=mosBuffer[0].rb;
		mx=mosBuffer[0].mx;
		my=mosBuffer[0].my;

		for(int i=0; i<nMosBufUsed; ++i)
		{
			mosBuffer[i]=mosBuffer[i+1];
		}
		--nMosBufUsed;
		return eventType;
	}
	else 
	{
		FsGetMouseState(lb,mb,rb,mx,my);
		return FSMOUSEEVENT_NONE;
	}
}

void FsSwapBuffers(void)
{
	FsSwapBuffersC();
}

int FsInkey(void)	
{
	return FSKEY_NULL;
}

int FsInkeyChar(void)
{
	return 0;
}

int FsGetKeyState(int fsKeyCode)
{
	return 0;
}

int FsCheckWindowExposure(void)
{
	auto e=exposure;
	exposure=0;
	return e;
}

void FsChangeToProgramDir(void)
{
	FsChangeToProgramDirC();
}

int FsGetNumCurrentTouch(void)
{
	const int nTouch=FsGetNumCurrentTouchC();
	if(nTouch<NEVTBUF)
	{
		return nTouch;
	}
	else
	{
		return NEVTBUF;
	}
}

const FsVec2i *FsGetCurrentTouch(void)
{
	const int nTouch=FsGetNumCurrentTouchC();
	const int *touchCoord=FsGetCurrentTouchC();

	for(int i=0; i<nTouch && i<NEVTBUF; ++i)
	{
		touchCache[i].v[0]=touchCoord[i*2  ];
		touchCache[i].v[1]=touchCoord[i*2+1];
	}

	return touchCache;
}
