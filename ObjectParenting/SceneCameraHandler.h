#pragma once
#include "ProtoCamera.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();
	
	void update();

	Matrix4x4 getSceneCameraViewMatrix();

private:

	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	

	ProtoCamera* sceneCamera;

};

