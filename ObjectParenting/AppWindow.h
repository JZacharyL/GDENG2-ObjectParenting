
#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Cube.h"
#include "Plane.h"
#include "InputListener.h"
#include "Point.h"
#include "GenericShape.h"
#include "SceneCameraHandler.h"


class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();
	
	static void initialize();
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	
	
	AppWindow(AppWindow const&) {}; //copy constructor is private
	AppWindow& operator=(AppWindow const&) {}; //assignment operator is private

	static AppWindow* sharedInstance;
	static float RandomFloat(float a, float b);

	


	
	Cube CubeArray[100];
	Plane firstPlane;
	Cube firstCube;
	Cube SecondCube;
	Cube ThirdCube;
	GenericShape genericShape;
	//ProtoCamera Camera;
	
	SwapChain * m_swap_chain;
	VertexBuffer* m_vb;
	
	VertexShader* m_vs;
	PixelShader* m_ps;

	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	

	
};
