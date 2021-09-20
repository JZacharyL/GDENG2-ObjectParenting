#include "Plane.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

Plane::Plane(std::string name, PrimitiveType type) : AGameObject(name,type)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);
	
	vertex vertex_list[] =
	{
		{Vector3D(-0.25f,-0.01f,-0.25f),	Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS1
		{Vector3D(-0.25f,0.01f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS2
		{Vector3D(0.25f,0.01f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS3
		{Vector3D(0.25f,-0.01f,-0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)},

		{Vector3D(0.25f,-0.01f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS1
		{Vector3D(0.25f,0.01f,0.25f),			Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS2
		{Vector3D(-0.25f,0.01f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)}, // POS3
		{Vector3D(-0.25f,-0.01f,0.25f),		Vector3D(1,1,1),		Vector3D(1,1,1)},
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

Plane::~Plane()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	this->constantBuffer->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;
	float rotSpeed = this->ticks + this->deltaTime;
	//this->setRotation(0.3f, rotSpeed, 0.0f);
	//this->setRotation(this->getLocalRotation().x, rotSpeed, this->getLocalRotation().z);

	/*
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	*/
}

void Plane::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	constant cc;

	if (this->deltaPos > 1.0f)
		this->deltaPos = 0.0f;

	else
		this->deltaPos += this->deltaTime / 10.0f;

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.x);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.y);
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.z);

	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix *= translationMatrix;

	//cc.m_world.setIdentity();
	cc.m_world = allMatrix;

	Matrix4x4 cameraMatrix = SceneCameraHandler::get()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	Camera::View projectionMatrix = SceneCameraHandler::get()->getSceneCameraProjectionMatrix();

	if(projectionMatrix == Camera::View::Perspective)
		cc.m_projection.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	else if(projectionMatrix == Camera::View::Orthographic)
		cc.m_projection.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	cc.m_time = ::GetTickCount() / 1000.0f;

	this->constantBuffer->update(deviceContext, &cc);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), this->constantBuffer);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME), this->constantBuffer);

	deviceContext->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME));
	deviceContext->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Plane::setAnimSpeed(float speed)
{
	this->speed = speed;
}

