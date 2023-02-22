#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	int 	id;
	GLuint 	GetTextureID();
	void 	Init(char * path);
	~Texture();
private:
	GLuint 	m_textureID;
};