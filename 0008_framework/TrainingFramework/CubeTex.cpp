#include "stdafx.h"
#include "CubeTex.h"
#include <string>

using namespace std;

CubeTex::CubeTex()
{
}
void CubeTex::Init(char* path)
{
	glGenTextures(1, &m_cubeTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTextureID);

	int width, height, bpp;
	char* imageData = LoadTGA(path, &width, &height, &bpp);
	char* colorBuffer[6];
	colorBuffer[2] = ExtractFace(imageData, width, width / 4, height / 3, width / 4, 0		   , bpp);
	colorBuffer[1] = ExtractFace(imageData, width, width / 4, height / 3, 0        , height / 3, bpp);
	colorBuffer[4] = ExtractFace(imageData, width, width / 4, height / 3, width / 4, height / 3, bpp);
	colorBuffer[0] = ExtractFace(imageData, width, width / 4, height / 3, 2*width/4, height / 3, bpp);
	colorBuffer[5] = ExtractFace(imageData, width, width / 4, height / 3, 3*width/4, height / 3, bpp);
	colorBuffer[3] = ExtractFace(imageData, width, width / 4, height / 3, width / 4, 2*height/3, bpp);
	// free the client memory
	delete imageData;
	for (int i = 0; i < 6; i++)
	{
		// load the image data into OpenGL ES texture resource
		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width / 4, height / 3, 0, GL_RGB, GL_UNSIGNED_BYTE, *&colorBuffer[i]);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width / 4, height / 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, *&colorBuffer[i]);
		}
		// free the client memory
		delete *&colorBuffer[i];
		//texture param.....
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// no GL_TEXTURE_MAG_FILTER with mipmap 
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint 	CubeTex::GetCubeTextureID()
{
	return m_cubeTextureID;
}

char* CubeTex::ExtractFace(char* pBuffer, int textureWidth, int faceWidth, int faceHeight, int offsetX, int offsetY, int bpp)
{
	char* pOutBuffer;

	int start = (offsetX + offsetY * textureWidth)* bpp / 8;
	pOutBuffer = new char[faceWidth * faceHeight * bpp / 8];
	for (int i = 0; i < faceHeight; i++)
	{
		memcpy(&pOutBuffer[i * faceWidth * bpp / 8], &pBuffer[start + i * textureWidth * bpp / 8], faceWidth * bpp / 8);
	}
	return pOutBuffer;
}

CubeTex::~CubeTex()
{
}
