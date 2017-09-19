/* ////////////////////////////////////////////////////////////

File Name: ysglslutil.h
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

#ifndef YSGLSLUTIL_IS_INCLUDED
#define YSGLSLUTIL_IS_INCLUDED
/* { */

#include "ysglheader.h"

/* Force Visual C++ to type-mismatching error. */
#pragma warning( error : 4028)
#pragma warning( error : 4047)

#ifdef __cplusplus
extern "C" {
#endif

void YsGLSLCompileAndLinkVertexAndFragmentShader(
    GLuint programId,
    GLuint vertexShaderId,
    const int nVertexShaderProgLine,const char * const vertexShaderProg[],
    GLuint fragmentShaderId,
    const int nFragShaderProgLine,const char * const fragShaderProg[]);

void YsGLSLCompileAndLinkVertexAndFragmentShaderSingleString(
    GLuint programId,
    GLuint vertexShaderId,
    const char vertexShaderProg[],
    GLuint fragmentShaderId,
    const char fragShaderProg[]);

void YsGLSLLoadIdentityMatrix3(GLuint uniformMatPos);
void YsGLSLLoadIdentityMatrix4(GLuint uniformMatPos);

#ifdef __cplusplus
}
#endif

/* } */
#endif
