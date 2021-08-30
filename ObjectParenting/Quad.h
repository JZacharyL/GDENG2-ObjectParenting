#pragma once
#include <DirectXMath.h>
#include "AGameObject.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class Quad : public AGameObject
{
public:
	Quad(string name);
	~Quad();
	
	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setAnimSpeed(float speed);

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
private:
	

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaRot = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};

