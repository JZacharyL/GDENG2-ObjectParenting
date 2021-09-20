#include "Quad.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
Quad::Quad(std::string name, PrimitiveType type) : AGameObject(name,type)
{

	ShaderNames shaderNames;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);
	
	vertex vertex_list[] =
	{
		{Vector3D(-0.25f,-0.25f,-0.25f),	Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS1
		{Vector3D(-0.25f,0.25f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS2
		{Vector3D(0.25f,0.25f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS3
		{Vector3D(0.25f,-0.25f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)},

		{Vector3D(0.25f,-0.25f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS1
		{Vector3D(0.25f,0.25f,0.25f),			Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS2
		{Vector3D(-0.25f,0.25f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS3
		{Vector3D(-0.25f,-0.25f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)},
	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		//Front
		0,1,2, //First triangle
		2,3,0, //Second triangle

		//Back
		4,5,6,
		6,7,4,

		//Top
		1,6,5,
		5,2,1,

		//Bottom
		7,0,3,
		3,4,7,

		//Right
		3,2,5,
		5,4,3,

		//Left
		7,6,1,
		1,0,7
	};

	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(index_list, ARRAYSIZE(index_list));

	constant cc;
	cc.m_time = 0;
	
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));
}

Quad::~Quad()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	AGameObject::~AGameObject();
}

void Quad::update(float deltaTime)
{
	
}

void Quad::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	constant cc;

	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	
	if (this->deltaPos > 1.0f)
		this->deltaPos = 0.0f;
	
	else
		this->deltaPos += this->deltaTime / 10.0f;
	
	this->deltaScale += this->deltaTime / 1.0f;
	
	//Matrix4x4 allMatrix; 
	//allMatrix.setIdentity();
	/*
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
	*/

	if(this->overrideMatrix)
	{
		cc.m_world = this->localMatrix;
	}
	else
	{
		this->updateLocalMatrix();
		cc.m_world = this->localMatrix;
	}
	


	//cc.m_world.setIdentity();
	

	Matrix4x4 cameraMatrix = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;
	
	Camera::View projectionMatrix = SceneCameraHandler::get()->getSceneCameraProjectionMatrix();

	if(projectionMatrix == Camera::View::Perspective)
		cc.m_projection.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	else if(projectionMatrix == Camera::View::Orthographic)
		cc.m_projection.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);


	cc.m_time = EngineTime::getDeltaTime();

	this->constantBuffer->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), this->constantBuffer);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME), this->constantBuffer);

	deviceContext->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME));
	deviceContext->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Quad::setAnimSpeed(float speed)
{
	this->speed = speed;
}

