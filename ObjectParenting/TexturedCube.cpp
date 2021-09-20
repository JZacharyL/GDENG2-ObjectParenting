#include "TexturedCube.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "SceneCameraHandler.h"
#include "TextureManager.h"
#include "VertexBuffer.h"
#include "TexturedVertexBuffer.h"
TexturedCube::TexturedCube(std::string name, PrimitiveType type) : Quad(name,type)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	Vector3D position_list[] =
	{
		{ Vector3D(-0.25f,-0.25f,-0.25f)},
		{ Vector3D(-0.25f,0.25f,-0.25f) },
		{ Vector3D(0.25f,0.25f,-0.25f) },
		{ Vector3D(0.25f,-0.25f,-0.25f)},

		//BACK FACE
		{ Vector3D(0.25f,-0.25f,0.5f) },
		{ Vector3D(0.25f,0.25f,0.5f) },
		{ Vector3D(-0.25f,0.25f,0.5f)},
		{ Vector3D(-0.25f,-0.25f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	TexturedCube::Vertex quadList[] =
	{
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }
	};

	this->vertexBuffer = GraphicsEngine::get()->createTexturedBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	//create constant buffer
	constant cc;
	cc.m_time = 0;

	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));

	

}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::draw(int width, int height)
{
	ShaderNames shaderNames;
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Texture* woodTex = (Texture*)TextureManager::getInstance()->createTextureFromFile(L"C:/Users/monet/source/repos/GDENG2ObjectParent/GDENG2ObjectParent/Assets/Textures/brick.png");
	constant cc;

	//set vertex shader and pixel shader for the object
	deviceContext->setTexture(woodTex);
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	

	Matrix4x4 allMatrix;
	allMatrix.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());

	//Matrix4x4 translationMatrix; translationMatrix.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), this->deltaPos));
	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());

	//Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::lerp(Vector3D::ones(), Vector3D(3.0f, 3.0f, 0.0f), (sin(this->deltaScale) +1.0f) / 2.0f));

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setIdentity();
	xMatrix.setRotationX(rotation.x);

	Matrix4x4 yMatrix; yMatrix.setIdentity();
	yMatrix.setRotationY(rotation.y);

	Matrix4x4 zMatrix; zMatrix.setIdentity();
	zMatrix.setRotationZ(rotation.z);

	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix *= translationMatrix;

	//cc.m_world.setIdentity();
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	Camera::View projectionMatrix = SceneCameraHandler::get()->getSceneCameraProjectionMatrix();

	if (projectionMatrix == Camera::View::Perspective)
		cc.m_projection.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	else if (projectionMatrix == Camera::View::Orthographic)
		cc.m_projection.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);


	cc.m_time = EngineTime::getDeltaTime();

	this->constantBuffer->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME), this->constantBuffer);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME), this->constantBuffer);

	deviceContext->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME));
	deviceContext->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}
