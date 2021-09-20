
#pragma once
#include <vector>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"
#include "Plane.h"
#include "InputListener.h"
#include "ImGui/imgui.h"

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void initialize();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	
	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;
	
	virtual void onLeftMouseDown(const Point& deltaMousePos) override;
	virtual void onLeftMouseUp(const Point& deltaMousePos) override;
	virtual void onRightMouseDown(const Point& deltaMousePos) override;
	virtual void onRightMouseUp(const Point& deltaMousePos) override;

	typedef std::vector<AGameObject*> QuadList;
	
private:
	SwapChain * m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

private:
	int nQuad = 50;
	QuadList quadList;
	double multiplier = 0;
	double increment = 0.01;

private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;

	float rotSpeed = 0.707f;
	float delta_rot_x = 0.0f;
	float delta_rot_y = 0.0f;

	float delta_Scale = 1.0f;

	float forward = 0.0f;
	float right = 0.0f;

	Matrix4x4 camera;
};

