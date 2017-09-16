#include "EndofLevel.h"

template <class T>
GenericArray <T>::GenericArray()
{
	dat=nullptr;
	lng=0;
}

template <class T>
GenericArray<T>::GenericArray(const GenericArray <T> &incoming)
{
	if(&incoming!=this)
	{
		lng=0;
		dat=nullptr;
		if(0<incoming.GetLength())
		{
			Resize(incoming.GetLength());
			for(int i=0; i<incoming.GetLength(); ++i)
			{
				auto ptr=incoming.Pointer();
				dat[i]=ptr[i];
			}
		}
	}
}

template <class T>
GenericArray <T> &GenericArray<T>::operator=(const GenericArray <T> &incoming)
{
	if(&incoming!=this)
	{
		if(0==incoming.GetLength())
		{
			this->CleanUp();
		}
		else if(0<incoming.GetLength())
		{
			Resize(incoming.GetLength());
			for(int i=0; i<incoming.GetLength(); ++i)
			{
				auto ptr=incoming.Pointer();
				dat[i]=ptr[i];
			}
		}
	}
	return *this;
}

template <class T>
GenericArray<T>::~GenericArray()
{
	CleanUp();
}
template <class T>
void GenericArray<T>::CleanUp(void)
{
	lng=0;
	if(nullptr!=dat)
	{
		delete [] dat;
		dat=nullptr;
	}
}

template <class T>
void GenericArray<T>::Resize(int newLng)
{
	if(0==newLng)
	{
		CleanUp();
	}
	else
	{
		char *newDat=new T [newLng];
		for(int i=0; i<newLng && i<lng; ++i)
		{
			newDat[i]=dat[i];
		}

		CleanUp();

		lng=newLng;
		dat=newDat;
	}
}

template <class T>
int GenericArray <T>::GetLength(void) const
{
	return lng;
}

template <class T>
T *GenericArray<T>::Pointer(void)
{
	return dat;
}
template <class T>
const T *GenericArray<T>::Pointer(void) const
{
	return dat;
}




void TextString::Print(void) const
{
	printf("%s\n",Pointer());
}

TextString::TextString()
{
}

TextString::TextString(const TextString &incoming)
{
	Set(incoming.GetPointer());
}

TextString &TextString::operator=(const TextString &incoming)
{
	Set(incoming.GetPointer());
	return *this;
}

TextString::~TextString()
{
	CleanUp();
}

const char *TextString::Fgets(FILE *fp)
{
	bool readSomething=false;

	CleanUp();

	char buf[16];
	while(nullptr!=fgets(buf,15,fp))
	{
		readSomething=true;

		for(int i=0; 0!=buf[i]; ++i)
		{
			Add(buf[i]);
		}

		const auto L=strlen(buf);
		if(0==isprint(buf[L-1]))
		{
			break;
		}
	}

	DeleteLastControlCode();

	if(true==readSomething)
	{
		return Pointer();
	}
	return nullptr;
}

void TextString::DeleteLastControlCode(void)
{
	auto str=Pointer();
	if(nullptr!=str)
	{
		int i;
		for(i=0; 0!=str[i]; ++i)
		{
		}
		for(i=i; 0<=i && 0==isprint(str[i]); --i)
		{
			str[i]=0;
		}
	}
}

void TextString::Add(char c)
{
	auto str=Pointer();
	if(nullptr==str)
	{
		const char newstr[2]={c,0};
		Set(newstr);
	}
	else
	{
		auto L=strlen(str);

		Resize(L+2);

		str=Pointer();

		str[L]=c;
		str[L+1]=0;
	}
}

void TextString::DeleteLast(void)
{
	auto str=Pointer();
	if(nullptr!=str)
	{
		auto L=strlen(str);
		if(0<L)
		{
			str[L-1]=0;
		}
	}
}

void TextString::Set(const char incoming[])
{
	auto L=strlen(incoming);
	Resize(L+1);

	auto str=Pointer();
	strcpy(str,incoming);
}

const char *TextString::GetPointer(void) const
{
	auto str=Pointer();
	if(nullptr!=str)
	{
		return str;
	}
	else
	{
		return "";
	}
}

int TextString::Strlen(void) const
{
	return strlen(GetPointer());
}

////////////////////////////////////////////////////////////


StringParser::StringParser()
{
	str=nullptr;
	wordTop=nullptr;
	wordLength=nullptr;
	nw=0;
}
StringParser::~StringParser()
{
	CleanUp();
}
void StringParser::CleanUp(void)
{
	if(nullptr!=str)
	{
		delete [] str;
		str=nullptr;
	}
	if(nullptr!=wordTop)
	{
		delete [] wordTop;
		wordTop=nullptr;
	}
	if(nullptr!=wordLength)
	{
		delete [] wordLength;
		wordTop=nullptr;
	}
}

int StringParser::NW(void)
{
	return nw;
}

int StringParser::Parse(const char s[])
{
	CleanUp();

	int n=strlen(s);
	str=new char [n+1];
	strcpy(str,s);

	wordTop=new int [1+n/2];
	wordLength=new int [1+n/2];
	nw=Parse(wordTop,wordLength,1+n/2,s);
	return nw;
}

int StringParser::Parse(int wordTop[],int wordLength[],int maxNumWord,const char str[])
{
	int state=0;  // 0:Blank   1:Visible Letter
	int nw=0;
	for(int i=0; 0!=str[i]; ++i)
	{
		switch(state)
		{
		case 0:
			if(' '!=str[i] && isprint(str[i]))
			{
				if(nw<maxNumWord)
				{
					wordTop[nw]=i;
					wordLength[nw]=1;
				}
				else
				{
					goto LOOPOUT;
				}
				++nw;
				state=1;
			}
			else
			{
			}
			break;
		case 1:
			if(' '!=str[i] && isprint(str[i]))
			{
				wordLength[nw-1]++;
			}
			else
			{
				state=0;
			}
			break;
		}
	}
LOOPOUT:

	return nw;
}

void StringParser::GetWord(char wd[],int maxn,int idx)
{
	wd[0]=0;
	if(0<=idx && idx<nw)
	{
		for(int i=0; i<wordLength[idx] && i<maxn; ++i)
		{
			wd[i]=str[wordTop[idx]+i];
			wd[i+1]=0;
		}
	}
}

////////////////////////////////////////////////////////////



OBJData::OBJData()
{
	a[0]=0.0;
	a[1]=0.0;
	a[2]=0.0;
}
OBJData::~OBJData()
{
	CleanUp();
}
void OBJData::CleanUp(void)
{
	tri.resize(0);
	copy.resize(0);
}

void OBJData::ReadObj(const char fn[])
{
	FILE *fp=fopen(fn,"r");
	if(nullptr!=fp)
	{
		TextString str;
		StringParser parser;

		//int state=0;  // 0:Outside facet  1:Inside facet
		int v=1,f=1,c=0;
		Vec3 p[9000];

		while(nullptr!=str.Fgets(fp))
		{
			parser.Parse(str.GetPointer());
			if(1<=parser.NW())
			{
				char wd[256];
				parser.GetWord(wd,255,0);

				if(0==strcmp(wd,"v") && 4<=parser.NW() && v<5000)
				{
					char xs[256],ys[256],zs[256];
					parser.GetWord(xs,255,1);
					parser.GetWord(ys,255,2);
					parser.GetWord(zs,255,3);
					p[v].v[0]=atof(xs);
					p[v].v[1]=atof(ys);
					p[v].v[2]=atof(zs);
					++v;
				}

				else if(0==strcmp(wd,"usemtl"))
				{
					char mat[256];
					parser.GetWord(mat,255,1);
					if(0==strcmp(mat,"material_0"))
					{
						color[c] = 0;
					}
					else if(0==strcmp(mat,"material_1"))
					{
						color[c] = 1;
					}
					else if(0==strcmp(mat,"material_2"))
					{
						color[c] = 2;
					}
					else if(0==strcmp(mat,"material_3"))
					{
						color[c] = 3;
					}
					else if(0==strcmp(mat,"material_4"))
					{
						color[c] = 4;
					}
					else if(0==strcmp(mat,"material_5"))
					{
						color[c] = 5;
					}
					else if(0==strcmp(mat,"material_6"))
					{
						color[c] = 6;
					}
					else if(0==strcmp(mat,"material_7"))
					{
						color[c] = 7;
					}
					else //material 8
					{
						color[c] = 8;
					}
					pos[c] = f;
					//printf("Color change to %d at face %d.\n",color[c],pos[c]);
					++c;
				}

				else if(0==strcmp(wd,"f") && 4<=parser.NW())
				{
					char xs[256],ys[256],zs[256];
					Triangle t;
					parser.GetWord(xs,255,1);
					t.p[0]=p[atoi(xs)];
					parser.GetWord(ys,255,2);
					t.p[1]=p[atoi(ys)];
					parser.GetWord(zs,255,3);
					t.p[2]=p[atoi(zs)];
					tri.push_back(t);
					++f;
				}
			}
		}
		color[c] = color[c-1];
		pos[c] = f+1;
		fclose(fp);

		copy = tri;
		move.v[0]=0.0;
		move.v[1]=0.0;
		move.v[2]=0.0;

		//printf("Found %d vertices.\n",v);
		//printf("Found %d faces.\n",f);
		//printf("Found %d colors.\n",c);
		//printf("Found %d triangles.\n",(int)tri.size());
	}
	else
	{
		printf("Failed to open file.\n");
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
	int i=1,c=0;

	glPushMatrix();
	glRotatef(a[0], 1.0, 0.0, 0.0);
	glRotatef(a[1], 0.0, 1.0, 0.0);
	glRotatef(a[2], 0.0, 0.0, 1.0);

	glBegin(GL_TRIANGLES);
	for(auto &t : copy)
	{
		if(i >= pos[c+1])
		{
			++c;
		}

		if(k==0)
		{
			switch (color[c])
			{
			case 0:
				glColor3f(0.000000,0.501961,1.000000);
				break;
			case 1:
				glColor3f(0.003922,0.239216,0.819608);
				break;
			case 2:
				glColor3f(0.776471,0.756863,0.737255);
				break;
			case 3:
				glColor3f(1.0,1.0,1.0);
				break;
			case 4:
				glColor3f(0.101961,0.101961,0.101961);
				break;
			case 5:
				glColor3f(0.0,0.0,0.0);
				break;
			case 6:
				glColor3f(1.0,0.874510,0.600000);
				break;
			case 7:
				glColor3f(0.709804,0.019608,0.019608);
				break;
			default:
				glColor3f(0.647059,0.513726,0.000000);
				break;
			}
		}

		else //if i=1
		{
			switch (color[c])
			{
			case 0:
				glColor3f(1.000000,0.201961,0.000000);
				break;
			case 1:
				glColor3f(0.819608,0.239216,0.003922);
				break;
			case 2:
				glColor3f(0.776471,0.756863,0.737255);
				break;
			case 3:
				glColor3f(1.0,1.0,1.0);
				break;
			case 4:
				glColor3f(0.101961,0.101961,0.101961);
				break;
			case 5:
				glColor3f(0.0,0.0,0.0);
				break;
			case 6:
				glColor3f(1.0,0.874510,0.600000);
				break;
			case 7:
				glColor3f(0.709804,0.019608,0.019608);
				break;
			default:
				glColor3f(0.647059,0.513726,0.000000);
				break;
			}
		}

		glVertex3d(t.p[0].v[0]+move.v[0], t.p[0].v[1]+move.v[1], t.p[0].v[2]+move.v[2]);
		glVertex3d(t.p[1].v[0]+move.v[0], t.p[1].v[1]+move.v[1], t.p[1].v[2]+move.v[2]);
		glVertex3d(t.p[2].v[0]+move.v[0], t.p[2].v[1]+move.v[1], t.p[2].v[2]+move.v[2]);
		++i;
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

		if(winner = 0)
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