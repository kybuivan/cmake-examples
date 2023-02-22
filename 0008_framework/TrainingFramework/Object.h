#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Shaders.h"
#include "Texture.h"
#include "CubeTex.h"
#include "Lights.h"

struct OBJECTS
{
	int 		objectID;
	int 		modelID;
	int 		numTexture;
	int* 		textureID;
	int 		numCubeTex;
	int* 		CubeTexID;
	int 		shaderID;
	int 		numLight;
	int* 		lightID;
	Vector3 	objectPos;
	Vector3 	objectRot;
	Vector3 	objectSca;
};

class Object
{
public:
	void 		Init();
	void 		Draw(ESContext *esContext);
	Matrix 		world;
	Matrix 		MVPMatrix;
	Vector3		m_camerapos;
	float		m_runtime;
	OBJECTS 	m_objectInfo;
	~Object();

	CubeTex*	m_cubeTex;
	Model* 		m_model;
	Texture* 	m_texture;
	Shaders* 	m_shader;
	Lights*		m_light;
};
