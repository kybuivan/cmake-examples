#include "stdafx.h"
#include "ResourceMgr.h"

ResourceMgr * ResourceMgr::ms_resourceMgr = nullptr;

void ResourceMgr::Init(char* path)
{
	FILE * f;

	if (fopen_s(&f, path, "rb") != 0)
	{
		printf("Can't load model");
		return;
	}

	char temppath[100];
	fscanf(f, "#HeightMap:\n");
	fscanf(f, "FILE %s\n", &temppath);

	int numModel;
	if (fscanf(f, "#Model: %d\n", &numModel) == 1 && numModel > 0)
	{
		m_listModels = new Model[numModel];
		for (int i = 0; i < numModel; i++)
		{
			fscanf(f, "ID %d\n", &m_listModels[i].id);
			char path[100];
			fscanf(f, "FILE %s\n", &path);
			char * pch = nullptr;
			pch = strstr(path, "Terrain");
			if (pch !=nullptr)
			{
				m_listModels[i].m_heightmapPath = temppath;
				int t = 0;
			}
			m_listModels[i].Init(path);
		}
	}
	int numTexture;
	if (fscanf(f, "#2D Texture: %d\n", &numTexture) == 1 && numTexture > 0)
	{
		m_listTextures = new Texture[numTexture];
		for (int i = 0; i < numTexture; i++)
		{
			fscanf(f, "ID %d\n", &m_listTextures[i].id);
			char path[100];
			fscanf(f, "FILE %s\n", &path);
			m_listTextures[i].Init(path);
		}
	}

	int numCubeTex;
	if (fscanf(f, "#Cube Textures: %d\n", &numCubeTex) == 1 && numCubeTex > 0)
	{
		m_listCubeTex = new CubeTex[numCubeTex];
		for (int i = 0; i < numCubeTex; i++)
		{
			fscanf(f, "ID %d\n", &m_listCubeTex[i].id);
			char path[100];
			fscanf(f, "FILE %s\n", &path);
			m_listCubeTex[i].Init(path);
		}
	}

	int numShader;
	if (fscanf(f, "#Shader: %d\n", &numShader) == 1 && numShader > 0)
	{
		m_listShaders = new Shaders[numShader];
		for (int i = 0; i < numShader; i++)
		{
			fscanf(f, "ID %d\n", &m_listShaders[i].id);
			char vsPath[100];
			char fsPath[100];
			fscanf(f, "VS %s\n", &vsPath);
			fscanf(f, "FS %s\n", &fsPath);
			m_listShaders[i].Init(vsPath, fsPath);
		}
	}

	int numLights;
	if (fscanf(f, "#Light: %d\n", &numLights) == 1 && numLights > 0)
	{
		m_listLights = new Lights[numLights];
		for (int i = 0; i < numLights; i++)
		{
			fscanf(f, "ID %d\n", &m_listLights[i].m_ID);
			fscanf(f, "POS %f %f %f\n", &m_listLights[i].m_pos.x, &m_listLights[i].m_pos.y, &m_listLights[i].m_pos.z);
			fscanf(f, "COLOR %f %f %f\n", &m_listLights[i].m_color.x, &m_listLights[i].m_color.y, &m_listLights[i].m_color.z);
		}
	}
	
	fclose(f);
}


ResourceMgr::~ResourceMgr()
{
	//printf("ResourceMgr::~ResourceMgr()");
	delete[] m_listModels;
	delete[] m_listShaders;
	delete[] m_listTextures;
	delete[] m_listCubeTex;
	delete[] m_listLights;
}