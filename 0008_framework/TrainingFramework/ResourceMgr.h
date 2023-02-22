#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "CubeTex.h"
#include "Lights.h"

class ResourceMgr
{
public:
	static void CreateResourceMgr()
	{
		if (ms_resourceMgr == nullptr)
			ms_resourceMgr = new ResourceMgr;
	}
	static ResourceMgr * GetResourceMgr()
	{
		return ms_resourceMgr;
	}
	static void DestroyResourceMgr()
	{
		if (ms_resourceMgr)
		{
			delete ms_resourceMgr;
			ms_resourceMgr = nullptr;
		}
	}
	Model* 		m_listModels = nullptr;
	Texture* 	m_listTextures = nullptr;
	Shaders* 	m_listShaders = nullptr;
	CubeTex*	m_listCubeTex = nullptr;
	Lights*		m_listLights = nullptr;
	void 		Init(char* path);
	
	~ResourceMgr();
protected:
	static ResourceMgr* ms_resourceMgr;
};

