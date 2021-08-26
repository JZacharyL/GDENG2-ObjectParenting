#pragma once
#include <string>
#include <vector>
#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Point.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};
__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
	unsigned int m_time;
};


class AGameObject
{
public:
	AGameObject();
	~AGameObject();

	void setLocalPosition(Vector3D position);
	void setLocalScale(Vector3D scale);
	void setLocalRotation(Vector3D rotation);
	void setAnimSpeed(float speed);

	//virtual void update(float deltatime) = 0;

	Vector3D getLocalPosition();
	Vector3D getLocalScale();
	Vector3D getLocalRotation();
	float getAnimSpeed();
private:
	

	Vector3D LocalScale;
	Vector3D LocalPosition;
	Vector3D LocalRotation;
	float AnimationSpeed;



};

