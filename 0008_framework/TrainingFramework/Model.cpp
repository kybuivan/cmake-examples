#include "stdafx.h"
#include "Model.h"
#include <string.h>
#include "HeightMap.h"

void Model::Init(char * path)
{
	FILE * f;

	if (fopen_s(&f, path, "rb") != 0)
	{
		printf("Can't load model");
		return;
	}
	
	int NrVertices = 0;
	Vertex * MVertices = nullptr;
	if (fscanf(f, "NrVertices: %d\n", &NrVertices) == 1)
	{
		MVertices = new Vertex[NrVertices];
		for (int i = 0; i < NrVertices; i++)
		{
			if (fscanf(f, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
				&MVertices[i].pos.x, &MVertices[i].pos.y, &MVertices[i].pos.z,
				&MVertices[i].normal.x, &MVertices[i].normal.y, &MVertices[i].normal.z,
				&MVertices[i].binormal.x, &MVertices[i].binormal.y, &MVertices[i].binormal.z,
				&MVertices[i].tangent.x, &MVertices[i].tangent.y, &MVertices[i].tangent.z,
				&MVertices[i].uv.x, &MVertices[i].uv.y))
			{
				/*printf(" %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n", i,
					MVertices[i].position.x, MVertices[i].position.y, MVertices[i].position.z,
					MVertices[i].normal.x, MVertices[i].normal.y, MVertices[i].normal.z,
					MVertices[i].binormal.x, MVertices[i].binormal.y, MVertices[i].binormal.z,
					MVertices[i].tangent.x, MVertices[i].tangent.y, MVertices[i].tangent.z,
					MVertices[i].uv.x, MVertices[i].uv.y);*/
			}
			else
			{
				printf("Can't load model");
			}
		}
	}
	unsigned int* indicesData = nullptr;
	if(fscanf(f, "NrIndices: %d\n", &NrIndices) == 1)
	{
		indicesData = new unsigned int[NrIndices];
		int temp = 0;
		for (int i = 0; i < NrIndices/3; i++)
		{
			fscanf(f, " %*d.    %u,    %u,    %u\n", &indicesData[temp], &indicesData[temp+1], &indicesData[temp+2]);
			temp = temp + 3;
		}
	}
	fclose(f);

	if (m_heightmapPath != nullptr)
	{
		GenerateTriGrid(MVertices, NrVertices);
	}
	//buffer object
	glGenBuffers(1, &m_vboModel);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboModel);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NrVertices, MVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboModel);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboModel);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NrIndices, indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// free the memory
	delete MVertices;
	delete indicesData;
}

GLuint Model::GetVboModel()
{
	return m_vboModel;
}
GLuint Model::GetIboModel()
{
	return m_iboModel;
}

void Model::GenerateTriGrid(Vertex*& verts, int& numVerts)
{
	int k = 0;
	int numVertRows = sqrt(numVerts);
	HeightMap mHeightmap(128, 128, m_heightmapPath, 0.05f, 0.0f);
	for (int i = 0; i < numVertRows; i++)
	{
		for (int j = 0; j < numVertRows; j++)
		{
			verts[k].pos.y = mHeightmap(i, j);
			++k;
		}
	}
}

Model::~Model()
{
	//printf("Model::~Model()");
}