#pragma once
#include "AGameObject.h"
#include <DirectXMath.h>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector2D.h"

class Bunny :
	public AGameObject
{
public:
	Bunny(string name);
	~Bunny();
	void update(float deltaTime) override;
	void draw(int width, int height) override;
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	Texture* BrickTex;
	Mesh* BunnyMesh;


	struct Vertex {
		Vector4D position;
		Vector2D texCoord;
	};

};
