#include "stdafx.h"

#include "Camera.h"
#include "math.h"

Camera::Camera()
{
	viewDirection = Vector3(0.0f, 0.0f, -1.0f);
	rightVector = Vector3(1.0f, 0.0f, 0.0f);
}

void Camera::setViewMatrix(Vector3 vPos, Vector3 tgPos, Vector3 upPos)
{
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (vPos.operator-(tgPos)).Normalize();
	xaxis = (upPos.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Matrix rotationView;
	rotationView.m[0][0] = xaxis.x; rotationView.m[0][1] = xaxis.y; rotationView.m[0][2] = xaxis.z; rotationView.m[0][3] = 0.0;
	rotationView.m[1][0] = yaxis.x; rotationView.m[1][1] = yaxis.y; rotationView.m[1][2] = yaxis.z; rotationView.m[1][3] = 0.0;
	rotationView.m[2][0] = zaxis.x; rotationView.m[2][1] = zaxis.y; rotationView.m[2][2] = zaxis.z; rotationView.m[2][3] = 0.0;
	rotationView.m[3][0] = 0.0;		rotationView.m[3][1] = 0.0;		rotationView.m[3][2] = 0.0;		rotationView.m[3][3] = 1.0;
	Matrix translationView;
	translationView.SetTranslation(-vPos);
	viewMatrix = translationView.operator*(rotationView.Transpose());
}

Matrix Camera::getViewMatrix()
{
	setViewMatrix(m_cameraPos, m_targetPos, upVector);
	return viewMatrix;
}

void Camera::Init(Vector3 vPos, Vector3 tgPos, int screenWidth, int screenHeight)
{
	m_cameraPos = vPos;
	m_targetPos = Vector3(tgPos.x, tgPos.y, tgPos.z);
	upVector = Vector3(0.0, 1.0, 0.0);
	deltaMove = (m_cameraPos - m_targetPos).Normalize() *deltaTime * MovementSpeed;
	setViewMatrix(m_cameraPos, m_targetPos, upVector);
	projectMatrix.SetPerspective(m_fovY, (GLfloat)screenWidth / screenHeight, m_nearPlane, m_farPlane);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
		case FORWARD:
			deltaMove = -(m_cameraPos.operator-(m_targetPos)).Normalize() * velocity;
			break;
		case BACKWARD:
			deltaMove = (m_cameraPos.operator-(m_targetPos)).Normalize() * velocity;
			break;
		case LEFT:
			{
				Vector3 strDirection = upVector.Cross(m_cameraPos.operator-(m_targetPos));
				deltaMove = -strDirection.Normalize() * velocity;
			}
			break;
		case RIGHT:
			{
				Vector3 strafeDirection = upVector.Cross(m_cameraPos.operator-(m_targetPos));
				deltaMove = strafeDirection.Normalize() * velocity;
			}
			break;
		default:
			break;
	}
	m_cameraPos += deltaMove;
	m_targetPos += deltaMove;
	setViewMatrix(m_cameraPos, m_targetPos, upVector);
}
void Camera::ProcessRotation(Camera_Movement direction, float deltaTime)
{
	float delta = MovementSpeed * deltaTime;
	
	switch (direction)
	{
		case TOP:
			RotationMatrixAroundX(delta);
			break;
		case BOTTOM:
			RotationMatrixAroundX(-delta);
			break;
		case ROTATIONLEFT:
			RotationMatrixAroundY(delta);
			break;
		case ROTATIONRIGHT:
			RotationMatrixAroundY(-delta);
			break;
		default:
			break;
	}
	setViewMatrix(m_cameraPos, m_targetPos, upVector);
}

Matrix Camera::GetWordMatric()
{
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (m_cameraPos.operator-(m_targetPos)).Normalize();
	xaxis = (upVector.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	Matrix rotationView;
	rotationView.m[0][0] = xaxis.x; rotationView.m[0][1] = xaxis.y; rotationView.m[0][2] = xaxis.z; rotationView.m[0][3] = 0.0;
	rotationView.m[1][0] = yaxis.x; rotationView.m[1][1] = yaxis.y; rotationView.m[1][2] = yaxis.z; rotationView.m[1][3] = 0.0;
	rotationView.m[2][0] = zaxis.x; rotationView.m[2][1] = zaxis.y; rotationView.m[2][2] = zaxis.z; rotationView.m[2][3] = 0.0;
	rotationView.m[3][0] = 0.0;		rotationView.m[3][1] = 0.0;		rotationView.m[3][2] = 0.0;		rotationView.m[3][3] = 1.0;
	Matrix translationView;
	translationView.SetTranslation(m_cameraPos);
	m_worldMatrix = rotationView.operator*(translationView);
	return m_worldMatrix;
}

void Camera::RotationMatrixAroundX(float delta)
{
	Vector4 localTarget = Vector4(0, 0, -(m_cameraPos - m_targetPos).Length(), 1);
	Matrix rotmatrixX;
	rotmatrixX.SetRotationX(delta);
	Vector4 localNewTarget = localTarget * rotmatrixX;
	Vector4 worldNewTarget = localNewTarget * GetWordMatric();
	m_targetPos = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationMatrixAroundY(float delta)
{
	Vector4 localTarget = Vector4(0, 0, -(m_cameraPos - m_targetPos).Length(), 1);
	Matrix rotmatrixY;
	rotmatrixY.SetRotationY(delta);
	Vector4 localNewTarget = localTarget * rotmatrixY;
	Vector4 worldNewTarget = localNewTarget * GetWordMatric();
	m_targetPos = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

Vector3 Camera::GetCameraPos()
{
	return m_cameraPos;
}

Camera::~Camera()
{

}