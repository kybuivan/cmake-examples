#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "Camera.h"
#include "Lights.h"

class SceneMgr
{
public:

	void 		Init(char* path, int screenWidth, int screenHeight);
	void 		Update(ESContext *esContext, float deltaTime, int keypress);
	void 		Draw(ESContext *esContext);
	Object* 	listObject;
	SceneMgr();
	~SceneMgr();
	static void CreateSceneMgr()
	{
		if (ms_sceneMgr == nullptr)
			ms_sceneMgr = new SceneMgr;
	}
	static SceneMgr* GetSceneMgr() { return ms_sceneMgr; }
	static void DestroySceneMgr()
	{
		if (ms_sceneMgr)
		{
			delete ms_sceneMgr;
			ms_sceneMgr = nullptr;
		}
	}

protected:
	static SceneMgr* ms_sceneMgr;

private:
	Camera	m_camera;
	Lights* m_listLights;
	float	m_runtime = 0;
	int		m_numObject;
	void 	OpenResource(char* path);
};

enum CameraFlags
{
	k_Left 			= (1 << 0), // the left side of the camera
	k_Right 		= (1 << 1), // the right side of the camera
	k_Forward 		= (1 << 2), // the forward side of the camera
	k_Backward 		= (1 << 3), // the backward side of the camera
	k_RotationLeft 	= (1 << 4), // rotation left side of the camera
	k_RotationRight = (1 << 5), // rotation right side of the camera
	k_Top 			= (1 << 6), // the top side of the camera
	k_Bottom 		= (1 << 7), // the bottom side of the camera
};