#ifndef ENDOFLEVEL_H_IS_INCLUDED
#define ENDOFLEVEL_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include "fssimplewindow.h"

const double YsPi=3.1415927;


////////////////////////////////////////////////////////////

template <class T>
class GenericArray
{
private:
	int lng;
	T *dat;

public:
	GenericArray();
	GenericArray(const GenericArray <T> &incoming);
	GenericArray &operator=(const GenericArray <T> &incoming);
	~GenericArray();
	void CleanUp(void);

	void Resize(int newLng);
	int GetLength(void) const;

protected:
	T *Pointer(void);
	const T *Pointer(void) const;
};

class TextString : public GenericArray <char>
{
public:
	TextString();
	TextString(const TextString &incoming);
	TextString &operator=(const TextString &incoming);
	~TextString();

	const char *Fgets(FILE *fp);
	void DeleteLastControlCode(void);

	void Add(char c);
	void DeleteLast(void);
	void Set(const char incoming[]);
	const char *GetPointer(void) const;

	int Strlen(void) const;

	void Print(void) const;
};

class StringParser
{
protected:
	char *str;
	int *wordTop,*wordLength;
	int nw;

public:
	StringParser();
	~StringParser();
	void CleanUp(void);

	int Parse(const char s[]);
protected:
	int Parse(int wordTop[],int wordLength[],int maxNumWord,const char str[]);

public:
	int NW(void);
	void GetWord(char wd[],int maxn,int i);
};


class Vec3
{
public:
	double v[3];
};

class Triangle
{
public:
	Vec3 p[3];
};

class OBJData
{
private:
	std::vector <Triangle> tri;
	std::vector <Triangle> copy;
	Vec3 move;
	int color[30],pos[30];
	double a[3];
public:
	OBJData();
	~OBJData();
	void CleanUp(void);

	void ReadObj(const char fn[]);
	void Move(double x1,double y1,double z1);
	void Rotate(double a1,double x1,double y1,double z1);
	void Draw(int i) const; // 0 = human winner , 1 = AI winner
};

class CameraObject
{
public:
	double x,y,z;
	double h,p,b;

	double fov,nearZ,farZ;

	CameraObject();
	void Initialize(void);
	void SetUpCameraProjection(void);
	void SetUpCameraTransformation(void);

	void GetForwardVector(double &vx,double &vy,double &vz);
};

class OrbitViewer : public CameraObject
{
public:
	double cx,cy,cz;
	double dist;

	OrbitViewer();
	void UpdateCameraPosition(void);
};

class Confetti											//Set up the Confetti Class
{
public:
	int  x1,x2,y1,y2,r,g,b;
	void Initialize(void);
	void Throw();
	void DrawConfetti(void);
};



#endif