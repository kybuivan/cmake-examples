#pragma once
#include "../Utilities/utilities.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	ROTATIONLEFT,
	ROTATIONRIGHT
};

class Camera
{
public:
	Camera();
	float 		deltaTime = 4.0f;
	void 		Init(Vector3 vPos, Vector3 tgPos, int screenWidth, int screenHeight);
	void 		setViewMatrix(Vector3 vPos, Vector3 tgPos, Vector3 upPos);
	Matrix 		viewMatrix, m_worldMatrix, matrix;
	Matrix 		getViewMatrix();
	Vector3		GetCameraPos();
	Vector3 	upVector, deltaMove;
	GLfloat 	m_fovY, m_nearPlane, m_farPlane;
	// Camera options
	Vector3 	viewDirection, rightVector;
	float 		MovementSpeed;
	void 		ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void 		ProcessRotation(Camera_Movement direction, float deltaTime);
	Matrix		projectMatrix;
	~Camera();
private:
	Vector3 	m_cameraPos, m_targetPos;
	Matrix 		GetWordMatric();
	void 		RotationMatrixAroundX(float delta);
	void 		RotationMatrixAroundY(float delta);
};