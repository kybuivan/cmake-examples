#pragma once
#include "Shaders.h"
#include <iostream>
#include "Vertex.h"

class Model
{
public:
	int 	id;
	int 	NrIndices = 0;
	void 	Init(char * path);
	char*	m_heightmapPath = nullptr;
	GLuint 	GetVboModel();
	GLuint 	GetIboModel();
	~Model();
private:
	/*  Functions   */
	GLuint 	m_iboModel, m_vboModel;
	void GenerateTriGrid(Vertex*& verts, int& numVerts);
};