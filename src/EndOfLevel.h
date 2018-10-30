#ifndef ENDOFLEVEL_H_IS_INCLUDED
#define ENDOFLEVEL_H_IS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include <array>

#include "fssimplewindow.h"

const double YsPi=3.1415927;

enum material_type {
	MATERIAL_0,
	MATERIAL_1,
	MATERIAL_2,
	MATERIAL_3,
	MATERIAL_4,
	MATERIAL_5,
	MATERIAL_6,
	MATERIAL_7,
	DEFAULT
};

class position_3d
{
public:
	position_3d() : v{0.0, 0.0, 0.0} { }
	std::array<double,3> v;
};

class tri_facet
{
public:
	std::array<unsigned, 3> vertex_id;
	material_type material;
};

class OBJData
{
private:
	std::vector<position_3d> m_vertices;
	std::vector<tri_facet> m_facets;
	position_3d move;
	float a[3];
public:
	OBJData();
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