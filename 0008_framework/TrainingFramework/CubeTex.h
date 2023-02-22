#pragma once
#include "../Utilities/utilities.h"

class CubeTex
{
public:
	int 	id;
	void	Init(char* path);
	GLuint 	GetCubeTextureID();
	CubeTex();
	~CubeTex();
private:
	char*	ExtractFace(char* pBuffer, int textureWidth, int faceWidth, int faceHeight, int offsetX, int offsetY, int bpp);
	GLuint 	m_cubeTextureID;
};

