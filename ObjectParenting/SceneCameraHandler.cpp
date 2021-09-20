#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::get()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize(RECT window)
{
	sharedInstance = new SceneCameraHandler(window);
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
	return this->sceneCamera->getViewMatrix();
}

Camera::View SceneCameraHandler::getSceneCameraProjectionMatrix()
{
	return this->sceneCamera->getView();
}

SceneCameraHandler::SceneCameraHandler(RECT window)
{
	this->sceneCamera = new Camera("SceneCamera", AGameObject::CAMERA);
	this->sceneCamera->initialize(window);
}

SceneCameraHandler::~SceneCameraHandler()
{
	delete this->sceneCamera;
}
