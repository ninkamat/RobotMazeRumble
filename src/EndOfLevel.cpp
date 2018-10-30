#include "EndOfLevel.h"
#include <fstream>
#include <sstream>
#include <iostream>

////////////////////////////////////////////////////////////

std::vector<std::string> parse_string(const std::string& str)
{
	std::istringstream iss(str);
	std::vector<std::string> words(
		(std::istream_iterator<std::string>{iss}),
		std::istream_iterator<std::string>());
	return words;
}

////////////////////////////////////////////////////////////

OBJData::OBJData()
{
	a[0]=0.0;
	a[1]=0.0;
	a[2]=0.0;
}

void OBJData::ReadObj(const char fn[])
{
	std::ifstream objectFile(fn, std::ios::in);
	if (!objectFile.fail())
	{
		std::string line;
		material_type current_material = DEFAULT;
		while(std::getline(objectFile, line))
		{
			auto words = parse_string(line);
			if (1 <= words.size())
			{
				auto first_word = words[0];
				if (first_word.compare("v") == 0 && words.size() >= 4)
				{
					position_3d vertex;
					auto second_word = words[1];
					auto third_word = words[2];
					auto fourth_word = words[3];
					vertex.v[0] = std::stod(second_word);
					vertex.v[1] = std::stod(third_word);
					vertex.v[2] = std::stod(fourth_word);
					m_vertices.push_back(vertex);
				}
				else if(first_word.compare("usemtl") == 0)
				{
					auto material_word = words[1];
					if (material_word.compare("material_0") == 0)
					{
						current_material = MATERIAL_0;
					}
					else if (material_word.compare("material_1") == 0)
					{
						current_material = MATERIAL_1;
					}
					else if (material_word.compare("material_2") == 0)
					{
						current_material = MATERIAL_2;
					}
					else if (material_word.compare("material_3") == 0)
					{
						current_material = MATERIAL_3;
					}
					else if (material_word.compare("material_4") == 0)
					{
						current_material = MATERIAL_4;
					}
					else if (material_word.compare("material_5") == 0)
					{
						current_material = MATERIAL_5;
					}
					else if (material_word.compare("material_6") == 0)
					{
						current_material = MATERIAL_6;
					}
					else if (material_word.compare("material_7") == 0)
					{
						current_material = MATERIAL_7;
					}
				}
				else if(first_word.compare("f") == 0 && words.size() >= 4)
				{
					tri_facet tri;
					tri.vertex_id[0] = std::stoi(words[1]) - 1;
					tri.vertex_id[1] = std::stoi(words[2]) - 1;
					tri.vertex_id[2] = std::stoi(words[3]) - 1;
					tri.material = current_material;
					m_facets.push_back(tri);
				}
			}
		}
	}
}

void OBJData::Move(double x1,double y1,double z1)
{
	move.v[0]+=x1;
	move.v[1]+=y1;
	move.v[2]+=z1;
}

void OBJData::Rotate(double a1,double x1,double y1,double z1)
{
	if(x1 == 1.0)
	{
		a[0]+=a1;
	}
	if(y1 == 1.0)
	{
		a[1]+=a1;
	}
	if(z1 == 1.0)
	{
		a[2]+=a1;
	}
}


void OBJData::Draw(int k) const
{
	// std::cout << "Draw for loop reached!" << std::endl;;
	glPushMatrix();
	glRotatef(a[0], 1.0, 0.0, 0.0);
	glRotatef(a[1], 0.0, 1.0, 0.0);
	glRotatef(a[2], 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	
	for(auto &current_facet : m_facets)
	{
		if(k==0)
		{
			switch (current_facet.material)
			{
			case MATERIAL_0:
				glColor3f(0.000000,0.501961,1.000000);
				break;
			case MATERIAL_1:
				glColor3f(0.003922,0.239216,0.819608);
				break;
			case MATERIAL_2:
				glColor3f(0.776471,0.756863,0.737255);
				break;
			case MATERIAL_3:
				glColor3f(1.0,1.0,1.0);
				break;
			case MATERIAL_4:
				glColor3f(0.101961,0.101961,0.101961);
				break;
			case MATERIAL_5:
				glColor3f(0.0,0.0,0.0);
				break;
			case MATERIAL_6:
				glColor3f(1.0,0.874510,0.600000);
				break;
			case MATERIAL_7:
				glColor3f(0.709804,0.019608,0.019608);
				break;
			default:
				glColor3f(0.647059,0.513726,0.000000);
				break;
			}
		}

		else //if i=1
		{
			switch (current_facet.material)
			{
			case MATERIAL_0:
				glColor3f(1.000000,0.201961,0.000000);
				break;
			case MATERIAL_1:
				glColor3f(0.819608,0.239216,0.003922);
				break;
			case MATERIAL_2:
				glColor3f(0.776471,0.756863,0.737255);
				break;
			case MATERIAL_3:
				glColor3f(1.0,1.0,1.0);
				break;
			case MATERIAL_4:
				glColor3f(0.101961,0.101961,0.101961);
				break;
			case MATERIAL_5:
				glColor3f(0.0,0.0,0.0);
				break;
			case MATERIAL_6:
				glColor3f(1.0,0.874510,0.600000);
				break;
			case MATERIAL_7:
				glColor3f(0.709804,0.019608,0.019608);
				break;
			default:
				glColor3f(0.647059,0.513726,0.000000);
				break;
			}
		}
		unsigned vertexIdx0 = current_facet.vertex_id[0];
		unsigned vertexIdx1 = current_facet.vertex_id[1];
		unsigned vertexIdx2 = current_facet.vertex_id[2];
		auto& vertex0 = m_vertices[vertexIdx0];
		auto& vertex1 = m_vertices[vertexIdx1];
		auto& vertex2 = m_vertices[vertexIdx2];
		// std::cout << "v(" << vertex0.v[0] << "," << vertex0.v[1] << "," << vertex0.v[2] << ")" << std::endl;
		glVertex3d(vertex0.v[0] + move.v[0], vertex0.v[1] + move.v[1], vertex0.v[2] + move.v[2]);
		glVertex3d(vertex1.v[0] + move.v[0], vertex1.v[1] + move.v[1], vertex1.v[2] + move.v[2]);
		glVertex3d(vertex2.v[0] + move.v[0], vertex2.v[1] + move.v[1], vertex2.v[2] + move.v[2]);
	}
	glEnd();
	glPopMatrix();
}


CameraObject::CameraObject()
{
	Initialize();
}

void CameraObject::Initialize(void)
{
	x=0;
	y=0;
	z=0;
	h=0;
	p=0;
	b=0;

	fov=YsPi/6.0;  // 30 degree
	nearZ=0.1;
	farZ=200.0;
}

void CameraObject::SetUpCameraProjection(void)
{
	int wid,hei;
	double aspect;

	FsGetWindowSize(wid,hei);
	aspect=(double)wid/(double)hei;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
	glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
	glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
	glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
	vx=-cos(p)*sin(h);
	vy= sin(p);
	vz=-cos(p)*cos(h);
}



OrbitViewer::OrbitViewer()
{
	cx=0.0;
	cy=0.0;
	cz=0.0;
	dist=10.0;
}

void OrbitViewer::UpdateCameraPosition(void)
{
	double vx,vy,vz;
	GetForwardVector(vx,vy,vz);

	x=cx-vx*dist;
	y=cy-vy*dist;
	z=cz-vz*dist;
}




void Confetti::Initialize(void)							//Randomly generate confetti
{
	x1=rand()%1200;
	y1=rand()%800 - 200;
	x2=x1 + (rand()%17) - (rand()%20);
	y2=y1 + (rand()%17) - (rand()%20);
	r=rand()%256;
	g=rand()%256;
	b=rand()%256;
}

void Confetti::Throw(void)								//Make the confetti fall
{
	y1+=1;
	y2+=1;
	int z1=rand()%1;
	int z2=rand()%1;
	x1=x1 + z1 - z2;									//Let the confetti move from side to side
	x2=x2 + z1 - z2;									//a little bit

	if(y1 > 800 && y2 > 800)							//If the confetti falls out of the screen
	{													//Send it back to the top
		y1= -10;
		y2= -10 - rand()%10;
	}
}

void Confetti::DrawConfetti(void)						//Draw the Confetti on the screen
{
	Throw();
	glLineWidth(3);
	glColor3ub(r,g,b);
	glBegin(GL_LINES);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glEnd();
}



int EndofLevel(int winner)
{
	OBJData stl;
	stl.ReadObj("crown.obj");

	OBJData bot;
	bot.ReadObj("2bot.obj");

	int terminate=0;
	OrbitViewer camera;

	camera.dist=400.0;

	camera.farZ=600.0;

	stl.Move(0.0,40.0,0.0);

	FsOpenWindow(16,16,1200,800,1);

	double size=1.0;
	double shift=1.0;

	Confetti celebrate[100];							//Initialize the celebration
	for(auto &i : celebrate)
	{
		i.Initialize();
	}

	while(0==terminate)
	{
		FsPollDevice();

		int wid,hei;
		FsGetWindowSize(wid,hei);


		stl.Rotate(1.0,0.0,1.0,0.0);
		bot.Rotate(-1.0,0.0,1.0,0.0);

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

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
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		// 2D drawing from here

		if(winner == 0)
		{
		for(auto &i : celebrate)						//Draw the confetti
		{
			i.DrawConfetti();
		}
		}

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;

}
