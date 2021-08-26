#pragma once
#include "AGameObject.h"
#include  "InputListener.h"
class ProtoCamera:  public InputListener, public AGameObject
{
public:
	ProtoCamera();
	~ProtoCamera();
	
	void update(float deltatime);
	void setListener();
	void removeListener();
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	
	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	Matrix4x4 getSceneCameraMatrix();
private:
	void updateViewMatrix();
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	Matrix4x4 CameraLocalMatrix;
	Vector3D localRot;
	
};

