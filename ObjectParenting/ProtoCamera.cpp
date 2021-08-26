#include "ProtoCamera.h"

#include "InputSystem.h"

ProtoCamera::ProtoCamera()
{
	InputSystem::get()->addListener(this);
	m_world_cam.setTranslation(Vector3D(0, 2, -2));
	this->CameraLocalMatrix.setIdentity();
	//this->CameraLocalMatrix.setTranslation(Vector3D(0, 1, -2));
}

ProtoCamera::~ProtoCamera()
{
}

void ProtoCamera::update(float deltatime)
{
	this->updateViewMatrix();
}


void ProtoCamera::onKeyDown(int key)
{
	/*Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float movespeed = 10.0f;*/
	if (key == 'W')
	{
		
		m_forward = 1.0f;
		
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
	}
	
}

void ProtoCamera::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void ProtoCamera::onMouseMove(const Point& delta_mouse_pos)
{
	
	

	
}

void ProtoCamera::onLeftMouseDown(const Point& mouse_pos)
{
	//m_world_cam.setTranslation(Vector3D(0, 1, -2));
}

void ProtoCamera::onLeftMouseUp(const Point& mouse_pos)
{
	
}

void ProtoCamera::onRightMouseDown(const Point& mouse_pos)
{
	int width = 1004;
	int height = 725;
	
	//localRot = this->getLocalRotation();
	//Inside on RightMouse down for now
	localRot = this->getLocalRotation();

	localRot.m_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	localRot.m_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	//std::cout << localRot.m_x << endl;
	//std::cout << localRot.m_y << endl;
	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;


	//InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void ProtoCamera::onRightMouseUp(const Point& mouse_pos)
{
}

Matrix4x4 ProtoCamera::getSceneCameraMatrix()
{
	return this->CameraLocalMatrix;
}

void ProtoCamera::updateViewMatrix()
{
	constant cc;
	//this->CameraLocalMatrix.setIdentity();
	
	Matrix4x4 world_cam;world_cam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	/*
	localRot = this->getLocalRotation();
	temp.setIdentity();
	temp.setRotationX(localRot.m_x);
	//std::cout << localRot.m_x << endl;
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRot.m_y);
	//std::cout << localRot.m_y << endl;
	world_cam *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	world_cam *= temp;
	*/
	
	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	
	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);
	
	m_world_cam = world_cam;
	


	world_cam.inverse();
	this->CameraLocalMatrix = world_cam;
	//cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(1004 - 0) / (float)(725 - 0)), 0.1f, 100.0f);  //first value is Bigger = wider
}

void ProtoCamera::setListener()
{
	InputSystem::get()->addListener(this);
}

void ProtoCamera::removeListener()
{
	InputSystem::get()->removeListener(this);
}
