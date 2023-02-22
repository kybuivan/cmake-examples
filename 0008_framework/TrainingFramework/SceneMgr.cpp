#include "stdafx.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

SceneMgr * SceneMgr::ms_sceneMgr = nullptr;

SceneMgr::SceneMgr()
{
}

void SceneMgr::Init(char* path, int screenWidth, int screenHeight)
{
	//Creation of Resource Manager
	ResourceMgr::CreateResourceMgr();
	ResourceMgr::GetResourceMgr()->Init("../Resources/ResourceManager.txt");

	OpenResource(path);
	for (int i = 0; i < m_numObject; i++)
	{
		listObject[i].m_model = &ResourceMgr::GetResourceMgr()->m_listModels[listObject[i].m_objectInfo.modelID];
		if (listObject[i].m_objectInfo.numTexture > 0)
		{
			listObject[i].m_texture = new Texture[listObject[i].m_objectInfo.numTexture];
			for (int j = 0; j < listObject[i].m_objectInfo.numTexture; j++)
			{
				listObject[i].m_texture[j] = *&ResourceMgr::GetResourceMgr()->m_listTextures[listObject[i].m_objectInfo.textureID[j]];
			}
		}
		for (int j = 0; j < listObject[i].m_objectInfo.numCubeTex; j++)
		{
			listObject[i].m_cubeTex = &ResourceMgr::GetResourceMgr()->m_listCubeTex[listObject[i].m_objectInfo.CubeTexID[j]];
		}
		
		listObject[i].m_shader = &ResourceMgr::GetResourceMgr()->m_listShaders[listObject[i].m_objectInfo.shaderID];

		if (listObject[i].m_objectInfo.numLight > 0)
		{
			listObject[i].m_light = new Lights[listObject[i].m_objectInfo.numLight];
			for (int j = 0; j < listObject[i].m_objectInfo.numLight; j++)
			{
				listObject[i].m_light[j] = *&ResourceMgr::GetResourceMgr()->m_listLights[listObject[i].m_objectInfo.lightID[j]];
			}
		}
		listObject[i].Init();
	}

	// Set up camera
	m_camera.Init(Vector3(0.0f, 1.5f, 5.0f), Vector3(0.0f, 0.0f, -1.0f), screenWidth, screenHeight);
}

void SceneMgr::Update(ESContext *esContext, float deltaTime, int keypress)
{
	m_runtime = m_runtime + deltaTime;

	if ((keypress & k_Backward) == k_Backward)
	{
		m_camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if ((keypress & k_Forward) == k_Forward)
	{
		m_camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if ((keypress & k_Right) == k_Right)
	{
		m_camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if ((keypress & k_Left) == k_Left)
	{
		m_camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if ((keypress & k_Top) == k_Top)
	{
		m_camera.ProcessRotation(TOP, deltaTime);
	}
	if ((keypress & k_Bottom) == k_Bottom)
	{
		m_camera.ProcessRotation(BOTTOM, deltaTime);
	}
	if ((keypress & k_RotationLeft) == k_RotationLeft)
	{
		m_camera.ProcessRotation(ROTATIONLEFT, deltaTime);
	}
	if ((keypress & k_RotationRight) == k_RotationRight)
	{
		m_camera.ProcessRotation(ROTATIONRIGHT, deltaTime);
	}
}
void SceneMgr::Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < m_numObject; i++)
	{
		listObject[i].MVPMatrix = listObject[i].world * m_camera.viewMatrix * m_camera.projectMatrix;
		listObject[i].m_runtime = m_runtime;
		listObject[i].m_camerapos = m_camera.GetCameraPos();
		listObject[i].Draw(esContext);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void SceneMgr::OpenResource(char* path)
{
	FILE * f;

	if (fopen_s(&f, path, "rb") != 0)
	{
		printf("Can't load model");
		return;
	}

	if (fscanf(f, "#Object: %d\n", &m_numObject) == 1 && m_numObject > 0)
	{
		listObject = new Object[m_numObject];
		for (int i = 0; i < m_numObject; i++)
		{
			fscanf(f, "ID %d\n", &listObject[i].m_objectInfo.objectID);
			fscanf(f, "MODEL %d\n", &listObject[i].m_objectInfo.modelID);
			fscanf(f, "TEXTURES %d\n", &listObject[i].m_objectInfo.numTexture);
			if (listObject[i].m_objectInfo.numTexture > 0)
			{
				listObject[i].m_objectInfo.textureID = new int[listObject[i].m_objectInfo.numTexture];
				for (int j = 0; j < listObject[i].m_objectInfo.numTexture; j++)
				{
					fscanf(f, "TEXTURE %d\n", &listObject[i].m_objectInfo.textureID[j]);
				}
			}
			fscanf(f, "CUBETEXTURES %d\n", &listObject[i].m_objectInfo.numCubeTex);
			if (listObject[i].m_objectInfo.numCubeTex > 0)
			{
				listObject[i].m_objectInfo.CubeTexID = new int[listObject[i].m_objectInfo.numCubeTex];
				for (int j = 0; j < listObject[i].m_objectInfo.numCubeTex; j++)
				{
					fscanf(f, "CUBETEX %d\n", &listObject[i].m_objectInfo.CubeTexID[j]);
				}
			}
			fscanf(f, "SHADER %d\n", &listObject[i].m_objectInfo.shaderID);
			fscanf(f, "LIGHTS %d\n", &listObject[i].m_objectInfo.numLight);
			if (listObject[i].m_objectInfo.numLight > 0)
			{
				listObject[i].m_objectInfo.lightID = new int[listObject[i].m_objectInfo.numLight];
				for (int j = 0; j < listObject[i].m_objectInfo.numLight; j++)
				{
					fscanf(f, "LIGHT %d\n", &listObject[i].m_objectInfo.lightID[j]);
				}
			}
			fscanf(f, "POSITION %f %f %f\n", &listObject[i].m_objectInfo.objectPos.x, &listObject[i].m_objectInfo.objectPos.y, &listObject[i].m_objectInfo.objectPos.z);
			fscanf(f, "ROTATION %f %f %f\n", &listObject[i].m_objectInfo.objectRot.x, &listObject[i].m_objectInfo.objectRot.y, &listObject[i].m_objectInfo.objectRot.z);
			fscanf(f, "SCALE %f %f %f\n", &listObject[i].m_objectInfo.objectSca.x, &listObject[i].m_objectInfo.objectSca.y, &listObject[i].m_objectInfo.objectSca.z);
		}
	}
	
	fscanf(f, "#CAMERA\n");
	fscanf(f, "NEAR %f\n", &m_camera.m_nearPlane);
	fscanf(f, "FAR %f\n", &m_camera.m_farPlane);
	fscanf(f, "FOV %f\n", &m_camera.m_fovY);
	fscanf(f, "SPEED %f\n", &m_camera.MovementSpeed);
	fclose(f);
}

SceneMgr::~SceneMgr()
{
	//printf("SceneMgr::~SceneMgr()");
	for (int i = 0; i < m_numObject; i++)
	{
		if (listObject[i].m_objectInfo.numTexture > 0)
		{
			
			delete[] listObject[i].m_texture;
		}
		if (listObject[i].m_objectInfo.numLight > 0)
		{
			delete[] listObject[i].m_light;
		}
	}
	delete[] listObject;
	ResourceMgr::DestroyResourceMgr();
}