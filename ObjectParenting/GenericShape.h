#pragma once
#include "AGameObject.h"
class GenericShape : public AGameObject
{
public:
	GenericShape();
	~GenericShape();
	void createShape();
	void update(float deltatime);
	void release();
	void updateQuadPosition(Vector3D position, Vector3D scale, float animspeed);
	void setCamera(Matrix4x4 worldCam);
	void RotateCube(int key);
	void RotateCubeMouse(const Point& delta_mouse_pos);
	void scaleUpWithMouse(const Point& delta_mouse_pos);
	void scaleDownWithMouse(const Point& delta_mouse_pos);
	void scaleNormalWithMouse(const Point& delta_mouse_pos);

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;
	bool accelspeed = false;


	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
	double m_New_delta_time = 0;

	float m_delta_pos = 0;
	long double m_delta_scale = 0;
	float m_delta_rot = 0;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_mouses_scale = 1.0f;

};

