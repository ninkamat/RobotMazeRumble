#include <stdlib.h>

#include "ysglslsharedrenderer.h"

// static struct YsGLSL3DRenderer *ysGLSLFlat3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorBillBoard3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorBillBoard3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLFlash3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLFlashByPointSprite3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColor3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorPerVtxShading3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorPerPixShading3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorPerVtxShading3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorPerPixShading3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorMarker3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorMarker3DRenderer=NULL;
// static struct YsGLSL3DRenderer *ysGLSLMonoColorMarkerByPointSprite3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorMarkerByPointSprite3DRenderer=NULL;
static struct YsGLSL3DRenderer *ysGLSLVariColorPointSprite3DRenderer=NULL;
static struct YsGLSLPlain2DRenderer *ysGLSLPlain2DRenderer=NULL;
static struct YsGLSLBitmapRenderer *ysGLSLBitmapRenderer=NULL;


static YSBOOL usePerPixRendering=YSFALSE;

#define YSGLSL_BIGENOUGH_BUT_NOTTOOBIG_NUMBER 32

static struct YsGLSL3DRenderer **GetAll3DRenderer(void)
{
	static struct YsGLSL3DRenderer *all3dRenderer[YSGLSL_BIGENOUGH_BUT_NOTTOOBIG_NUMBER];

	int i=0;
//	all3dRenderer[i++]=ysGLSLFlat3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorBillBoard3DRenderer;
// 	all3dRenderer[i++]=ysGLSLMonoColorBillBoard3DRenderer;
	all3dRenderer[i++]=ysGLSLFlash3DRenderer;
	all3dRenderer[i++]=ysGLSLFlashByPointSprite3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColor3DRenderer;
// 	all3dRenderer[i++]=ysGLSLMonoColorPerVtxShading3DRenderer;
// 	all3dRenderer[i++]=ysGLSLMonoColorPerPixShading3DRenderer;
// 	all3dRenderer[i++]=ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer;
// 	all3dRenderer[i++]=ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorPerVtxShading3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorPerPixShading3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer;
//	all3dRenderer[i++]=ysGLSLMonoColorMarker3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorMarker3DRenderer;
//	all3dRenderer[i++]=ysGLSLMonoColorMarkerByPointSprite3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorMarkerByPointSprite3DRenderer;
	all3dRenderer[i++]=ysGLSLVariColorPointSprite3DRenderer;
	all3dRenderer[i++]=NULL;
	if(YSGLSL_BIGENOUGH_BUT_NOTTOOBIG_NUMBER<i)
	{
		printf("%s %d\n",__FUNCTION__,__LINE__);
		printf("Buffer Overflow!!  Increase the buffer size!!\n");
		exit(1);
	}
	return all3dRenderer;
}

static struct YsGLSL3DRenderer **GetAll3DRendererWithLight(void)
{
	static struct YsGLSL3DRenderer *all3DRendererWithLight[YSGLSL_BIGENOUGH_BUT_NOTTOOBIG_NUMBER];

	int i=0;
// 	all3DRendererWithLight[i++]=ysGLSLMonoColorPerVtxShading3DRenderer;
// 	all3DRendererWithLight[i++]=ysGLSLMonoColorPerPixShading3DRenderer;
// 	all3DRendererWithLight[i++]=ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer;
// 	all3DRendererWithLight[i++]=ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer;
	all3DRendererWithLight[i++]=ysGLSLVariColorPerVtxShading3DRenderer;
	all3DRendererWithLight[i++]=ysGLSLVariColorPerPixShading3DRenderer;
	all3DRendererWithLight[i++]=ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer;
	all3DRendererWithLight[i++]=ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer;
	all3DRendererWithLight[i++]=NULL;
	if(YSGLSL_BIGENOUGH_BUT_NOTTOOBIG_NUMBER<i)
	{
		printf("%s %d\n",__FUNCTION__,__LINE__);
		printf("Buffer Overflow!!  Increase the buffer size!!\n");
		exit(1);
	}
	return all3DRendererWithLight;
}



YSRESULT YsGLSLCreateSharedRenderer(void)
{
//	if(NULL==ysGLSLFlat3DRenderer)
//	{
//		ysGLSLFlat3DRenderer=YsGLSLCreateFlat3DRenderer();
//	}
	if(NULL==ysGLSLVariColorBillBoard3DRenderer)
	{
		ysGLSLVariColorBillBoard3DRenderer=YsGLSLCreateVariColorBillBoard3DRenderer();
	}
// 	if(NULL==ysGLSLMonoColorBillBoard3DRenderer)
// 	{
// 		ysGLSLMonoColorBillBoard3DRenderer=YsGLSLCreateMonoColorBillBoard3DRenderer();
// 	}
	if(NULL==ysGLSLFlash3DRenderer)
	{
		ysGLSLFlash3DRenderer=YsGLSLCreateFlash3DRenderer();
	}
	if(NULL==ysGLSLFlashByPointSprite3DRenderer)
	{
		ysGLSLFlashByPointSprite3DRenderer=YsGLSLCreateFlashByPointSprite3DRenderer();
	}
	if(NULL==ysGLSLVariColor3DRenderer)
	{
		ysGLSLVariColor3DRenderer=YsGLSLCreateVariColor3DRenderer();
	}
// 	if(NULL==ysGLSLMonoColorPerVtxShading3DRenderer)
// 	{
// 		ysGLSLMonoColorPerVtxShading3DRenderer=YsGLSLCreateMonoColorPerVtxShading3DRenderer();
// 	}
// 	if(NULL==ysGLSLMonoColorPerPixShading3DRenderer)
// 	{
// 		ysGLSLMonoColorPerPixShading3DRenderer=YsGLSLCreateMonoColorPerPixShading3DRenderer();
// 	}
// 	if(NULL==ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer)
// 	{
// 		ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer=YsGLSLCreateMonoColorPerVtxShadingWithTexCoord3DRenderer();
// 	}
// 	if(NULL==ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer)
// 	{
// 		ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer=YsGLSLCreateMonoColorPerPixShadingWithTexCoord3DRenderer();
// 	}
	if(NULL==ysGLSLVariColorPerVtxShading3DRenderer)
	{
		ysGLSLVariColorPerVtxShading3DRenderer=YsGLSLCreateVariColorPerVtxShading3DRenderer();
	}
	if(NULL==ysGLSLVariColorPerPixShading3DRenderer)
	{
		ysGLSLVariColorPerPixShading3DRenderer=YsGLSLCreateVariColorPerPixShading3DRenderer();
	}
	if(NULL==ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer)
	{
		ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer=YsGLSLCreateVariColorPerVtxShadingWithTexCoord3DRenderer();
	}
	if(NULL==ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer)
	{
		ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer=YsGLSLCreateVariColorPerPixShadingWithTexCoord3DRenderer();
	}

	if(NULL==ysGLSLPlain2DRenderer)
	{
		ysGLSLPlain2DRenderer=YsGLSLCreatePlain2DRenderer();
	}

	if(NULL==ysGLSLBitmapRenderer)
	{
		ysGLSLBitmapRenderer=YsGLSLCreateBitmapRenderer();
	}

// 	if(NULL==ysGLSLMonoColorMarker3DRenderer)
// 	{
// 		ysGLSLMonoColorMarker3DRenderer=YsGLSLCreateMonoColorMarker3DRenderer();
// 	}
	if(NULL==ysGLSLVariColorMarker3DRenderer)
	{
		ysGLSLVariColorMarker3DRenderer=YsGLSLCreateVariColorMarker3DRenderer();
	}

// 	if(NULL==ysGLSLMonoColorMarkerByPointSprite3DRenderer)
// 	{
// 		ysGLSLMonoColorMarkerByPointSprite3DRenderer=YsGLSLCreateMonoColorMarkerByPointSprite3DRenderer();
// 	}
	if(NULL==ysGLSLVariColorMarkerByPointSprite3DRenderer)
	{
		ysGLSLVariColorMarkerByPointSprite3DRenderer=YsGLSLCreateVariColorMarkerByPointSprite3DRenderer();
	}
	if(NULL==ysGLSLVariColorPointSprite3DRenderer)
	{
		ysGLSLVariColorPointSprite3DRenderer=YsGLSLCreateVariColorPointSprite3DRenderer();
	}

	return YSOK;
}

YSRESULT YsGLSLDeleteSharedRenderer(void)
{
//	if(NULL!=ysGLSLFlat3DRenderer)
//	{
//		YsGLSLDelete3DRenderer(ysGLSLFlat3DRenderer);
//		ysGLSLFlat3DRenderer=NULL;
//	}
	if(NULL!=ysGLSLFlash3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLFlash3DRenderer);
		ysGLSLFlash3DRenderer=NULL;
	}
	if(NULL!=ysGLSLVariColorBillBoard3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorBillBoard3DRenderer);
		ysGLSLVariColorBillBoard3DRenderer=NULL;
	}
// 	if(NULL!=ysGLSLMonoColorBillBoard3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorBillBoard3DRenderer);
// 		ysGLSLMonoColorBillBoard3DRenderer=NULL;
// 	}
	if(NULL!=ysGLSLVariColor3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColor3DRenderer);
		ysGLSLVariColor3DRenderer=NULL;
	}
// 	if(NULL!=ysGLSLMonoColorPerVtxShading3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorPerVtxShading3DRenderer);
// 		ysGLSLMonoColorPerVtxShading3DRenderer=NULL;
// 	}
// 	if(NULL!=ysGLSLMonoColorPerPixShading3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorPerPixShading3DRenderer);
// 		ysGLSLMonoColorPerPixShading3DRenderer=NULL;
// 	}
// 	if(NULL!=ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer);
// 		ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer=NULL;
// 	}
// 	if(NULL!=ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer);
// 		ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer=NULL;
// 	}
	if(NULL!=ysGLSLVariColorPerVtxShading3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorPerVtxShading3DRenderer);
		ysGLSLVariColorPerVtxShading3DRenderer=NULL;
	}
	if(NULL!=ysGLSLVariColorPerPixShading3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorPerPixShading3DRenderer);
		ysGLSLVariColorPerPixShading3DRenderer=NULL;
	}
	if(NULL!=ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer);
		ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer=NULL;
	}
	if(NULL!=ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer);
		ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer=NULL;
	}

	if(NULL!=ysGLSLPlain2DRenderer)
	{
		YsGLSLDeletePlain2DRenderer(ysGLSLPlain2DRenderer);
		ysGLSLPlain2DRenderer=NULL;
	}

	if(NULL!=ysGLSLBitmapRenderer)
	{
		YsGLSLDeleteBitmapRenderer(ysGLSLBitmapRenderer);
		ysGLSLBitmapRenderer=NULL;
	}

// 	if(NULL!=ysGLSLMonoColorMarker3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorMarker3DRenderer);
// 		ysGLSLMonoColorMarker3DRenderer=NULL;
// 	}
	if(NULL!=ysGLSLVariColorMarker3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorMarker3DRenderer);
		ysGLSLVariColorMarker3DRenderer=NULL;
	}

// 	if(NULL!=ysGLSLMonoColorMarkerByPointSprite3DRenderer)
// 	{
// 		YsGLSLDelete3DRenderer(ysGLSLMonoColorMarkerByPointSprite3DRenderer);
// 		ysGLSLMonoColorMarkerByPointSprite3DRenderer=NULL;
// 	}
	if(NULL!=ysGLSLVariColorMarkerByPointSprite3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorMarkerByPointSprite3DRenderer);
		ysGLSLVariColorMarkerByPointSprite3DRenderer=NULL;
	}
	if(NULL==ysGLSLVariColorPointSprite3DRenderer)
	{
		YsGLSLDelete3DRenderer(ysGLSLVariColorPointSprite3DRenderer);
		ysGLSLVariColorPointSprite3DRenderer=NULL;
	}

	return YSOK;
}

struct YsGLSL3DRenderer *YsGLSLSharedFlat3DRenderer(void)
{
	return ysGLSLVariColor3DRenderer; // ysGLSLFlat3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorBillBoard3DRenderer(void)
{
	return ysGLSLVariColorBillBoard3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorBillBoard3DRenderer(void)
{
	return ysGLSLVariColorBillBoard3DRenderer; // ysGLSLMonoColorBillBoard3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedFlash3DRenderer(void)
{
	return ysGLSLFlash3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedFlashByPointSprite3DRenderer(void)
{
	return ysGLSLFlashByPointSprite3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColor3DRenderer(void)
{
	return ysGLSLVariColor3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorPerVtxShading3DRenderer(void)
{
	return ysGLSLVariColorPerVtxShading3DRenderer; // ysGLSLMonoColorPerVtxShading3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorPerPixShading3DRenderer(void)
{
	return ysGLSLVariColorPerPixShading3DRenderer; // ysGLSLMonoColorPerPixShading3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorPerVtxShading3DRenderer(void)
{
	return ysGLSLVariColorPerVtxShading3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorPerPixShading3DRenderer(void)
{
	return ysGLSLVariColorPerPixShading3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorPerVtxShadingWithTexCoord3DRenderer(void)
{
	return ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer; // ysGLSLMonoColorPerVtxShadingWithTexCoord3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorPerPixShadingWithTexCoord3DRenderer(void)
{
	return ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer; // ysGLSLMonoColorPerPixShadingWithTexCoord3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorPerVtxShadingWithTexCoord3DRenderer(void)
{
	return ysGLSLVariColorPerVtxShadingWithTexCoord3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorPerPixShadingWithTexCoord3DRenderer(void)
{
	return ysGLSLVariColorPerPixShadingWithTexCoord3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorMarker3DRenderer(void)
{
	return ysGLSLVariColorMarker3DRenderer; // ysGLSLMonoColorMarker3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorMarker3DRenderer(void)
{
	return ysGLSLVariColorMarker3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorMarkerByPointSprite3DRenderer(void)
{
	return ysGLSLVariColorMarkerByPointSprite3DRenderer; // ysGLSLMonoColorMarkerByPointSprite3DRenderer;
}
struct YsGLSL3DRenderer *YsGLSLSharedVariColorMarkerByPointSprite3DRenderer(void)
{
	return ysGLSLVariColorMarkerByPointSprite3DRenderer;
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorPointSprite3DRenderer(void)
{
	return ysGLSLVariColorPointSprite3DRenderer;
}

struct YsGLSLPlain2DRenderer *YsGLSLSharedPlain2DRenderer(void)
{
	return ysGLSLPlain2DRenderer;
}

struct YsGLSLBitmapRenderer *YsGLSLSharedBitmapRenderer(void)
{
	return ysGLSLBitmapRenderer;
}

////////////////////////////////////////////////////////////

void YsGLSLSetPerPixRendering(YSBOOL perPix)
{
	usePerPixRendering=perPix;
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorShaded3DRenderer(void)
{
	if(YSTRUE==usePerPixRendering)
	{
		return YsGLSLSharedMonoColorPerPixShading3DRenderer();
	}
	else
	{
		return YsGLSLSharedMonoColorPerVtxShading3DRenderer();
	}
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorShaded3DRenderer(void)
{
	if(YSTRUE==usePerPixRendering)
	{
		return YsGLSLSharedVariColorPerPixShading3DRenderer();
	}
	else
	{
		return YsGLSLSharedVariColorPerVtxShading3DRenderer();
	}
}

struct YsGLSL3DRenderer *YsGLSLSharedMonoColorShadedWithTexCoord3DRenderer(void)
{
	if(YSTRUE==usePerPixRendering)
	{
		return YsGLSLSharedMonoColorPerPixShadingWithTexCoord3DRenderer();
	}
	else
	{
		return YsGLSLSharedMonoColorPerVtxShadingWithTexCoord3DRenderer();
	}
}

struct YsGLSL3DRenderer *YsGLSLSharedVariColorShadedWithTexCoord3DRenderer(void)
{
	if(YSTRUE==usePerPixRendering)
	{
		return YsGLSLSharedVariColorPerPixShadingWithTexCoord3DRenderer();
	}
	else
	{
		return YsGLSLSharedVariColorPerVtxShadingWithTexCoord3DRenderer();
	}
}

YSRESULT YsGLSLSetShared3DRendererAlphaCutOff(GLfloat alphaCutOff)
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRenderer();

	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererAlphaCutOff(rendererArray[i],alphaCutOff);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererFog(int enableFog,const GLfloat density,const GLfloat fogColor[4])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRenderer();

	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererUniformFogEnabled(rendererArray[i],enableFog);
		YsGLSLSet3DRendererUniformFogDensity(rendererArray[i],density);
		YsGLSLSet3DRendererUniformFogColor(rendererArray[i],fogColor);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererProjection(const GLfloat proj[16])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRenderer();

	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererProjectionfv(rendererArray[i],proj);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererModelView(const GLfloat modelview[16])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRenderer();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererModelViewfv(rendererArray[i],modelview);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererDirectionalLightfv(int lightIdx,const GLfloat dir[3])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererUniformLightDirectionfv(rendererArray[i],lightIdx,dir);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererDirectionalLightInCameraCoordinatefv(int lightIdx,const GLfloat dir[3])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererUniformLightDirectionInCameraCoordinatefv(rendererArray[i],lightIdx,dir);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererLightColor(int idx,const GLfloat color[3])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererLightColor(rendererArray[i],idx,color);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererAmbientColor(const GLfloat color[3])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererAmbientColor(rendererArray[i],color);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererSpecularColor(const GLfloat color[3])
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererSpecularColor(rendererArray[i],color);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererSpecularExponent(const GLfloat exponent)
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRendererWithLight();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererSpecularExponent(rendererArray[i],exponent);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

YSRESULT YsGLSLSetShared3DRendererViewPortDimension(const GLfloat wid,const GLfloat hei)
{
	GLuint prevProgramId;
	struct YsGLSL3DRenderer **rendererArray;
	int i;

	rendererArray=GetAll3DRenderer();
	glGetIntegerv(GL_CURRENT_PROGRAM,(GLint *)&prevProgramId);

	for(i=0; NULL!=rendererArray[i]; ++i)
	{
		YsGLSLUse3DRenderer(rendererArray[i]);
		YsGLSLSet3DRendererViewportDimensionf(rendererArray[i],wid,hei);
		YsGLSLEndUse3DRenderer(rendererArray[i]);
	}

	glUseProgram(prevProgramId);

	return YSOK;
}

