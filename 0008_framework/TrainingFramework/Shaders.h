#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint 	program, vertexShader, fragmentShader;
	char 	fileVS[260];
	char 	fileFS[260];
	int 	id;
	GLint 	positionAttribute;
	GLint	uvAttribute;
	GLint	normAttribute;
	GLint	bitangentAttribute;
	GLint	tangentAttribute;
	GLint	iCubeTexLoc;
	GLint	iTextureLoc;
	GLint	iTextureLoc1;
	GLint	iTextureLoc2;
	GLint	iTextureLoc3;
	GLint	lightPos1;
	GLint	lightColor1;
	GLint 	wvpLoc;
	GLint	cameraPos;
	GLint	runTime;
	GLint	worldLoc;
	int 	Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};