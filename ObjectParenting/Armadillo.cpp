#include "Armadillo.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "SceneCameraHandler.h"
#include "TextureManager.h"
#include "VertexBuffer.h"
#include "TexturedVertexBuffer.h"
#include "Mesh.h"
#include "MeshManager.h"
Armadillo::Armadillo(std::string name, PrimitiveType type) : AGameObject(name, type)
{

	//cout << "Textured Armadillo constructor " << endl;
	ArmadilloMesh = (Mesh*)MeshManager::getInstance()->createMeshFromFile(L"C:/Users/monet/source/repos/GDENG2ObjectParent/GDENG2ObjectParent/Assets/objects/Armadillo.obj");
	//create constant buffer
	//cout << "done getting Armadillo instance " << endl;
	constant cc;
	cc.m_time = 0;

	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));


}

Armadillo::~Armadillo()
{
}
void Armadillo::update(float deltaTime)
{

}
void Armadillo::draw(int width, int height)
{
	ShaderNames shaderNames;
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	//BrickTex = (Texture*)TextureManager::getInstance()->createTextureFromFile(L"C:/Users/monet/source/repos/GDENG2ObjectParent/GDENG2ObjectParent/Assets/Textures/wood.png");
	constant cc;

	//set vertex shader and pixel shader for the object
	//deviceContext->setTexture(BrickTex);
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

	deviceContext->setIndexBuffer(ArmadilloMesh->getIndexBuffer());
	deviceContext->setVertexBuffer(ArmadilloMesh->getVertexBuffer());

	deviceContext->drawIndexedTriangleList(ArmadilloMesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}
