#include "SceneCameraHandler.h"
SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;
SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
	delete sharedInstance;
}

void SceneCameraHandler::update()
{
	this->sceneCamera->update(EngineTime::getDeltaTime());
	
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return this->sceneCamera->getSceneCameraMatrix();
	
}
SceneCameraHandler::SceneCameraHandler()
{
	this->sceneCamera = new ProtoCamera();
}

SceneCameraHandler::~SceneCameraHandler()
{
	delete this->sceneCamera;
}
