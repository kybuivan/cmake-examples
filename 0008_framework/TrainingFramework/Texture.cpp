#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Texture.h"


void Texture::Init(char * path)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	// save texture vertices and indices

	int width, height, bpp;
	char *imageData = LoadTGA(path, &width, &height, &bpp);
	
	// load the image data into OpenGL ES texture resource
	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	// free the client memory
	delete[] imageData;

	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetTextureID()
{
	return m_textureID;
}

Texture::~Texture()
{
	/*glDeleteTextures(1, &textureID);
	glDeleteTextures(1, &texVertices);
	glDeleteTextures(1, &texIndices);*/
}