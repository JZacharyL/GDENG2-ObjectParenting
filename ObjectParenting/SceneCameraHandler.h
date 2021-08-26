#pragma once
#include "Camera.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* get();
	static void initialize(RECT window);
	static void destroy();

	void update();
	

	Matrix4x4 getSceneCameraViewMatrix();
	Camera::View getSceneCameraProjectionMatrix();

private:
	SceneCameraHandler(RECT window);
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;
	
	Camera* sceneCamera;
	RECT window;
};

