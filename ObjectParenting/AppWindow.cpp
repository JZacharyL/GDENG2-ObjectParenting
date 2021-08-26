#include <iostream>
#include <string>
#include <Windows.h>
#include "AppWindow.h"
#include "InputSystem.h"
#include "UIManager.h"
AppWindow::AppWindow()
{

}


AppWindow::~AppWindow()
{
}
void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	
	
	Window::onCreate();

	InputSystem::get()->addListener(this);
	//InputSystem::get()->showCursor(false);

	SceneCameraHandler::getInstance()->initialize();
	
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	UIManager::getInstance()->initialize(this->m_hwnd);

	UIManager::getInstance()->setEnabled("CREDITS_SCREEN",false);
	UIManager::getInstance()->setEnabled("COLORUI_SCREEN", false);
	for (int i = 0; i < 100; i++)
	{
		float x = RandomFloat(-0.75f, 0.75f);
		float y = RandomFloat(-0.75f, 0.75f);
		float z = RandomFloat(-0.75f, 0.75f);
		CubeArray[i].createShape();
		CubeArray[i].setLocalPosition(Vector3D(x, y, z));
		CubeArray[i].setLocalScale(Vector3D(.25, 0.25, 0.25));
		CubeArray[i].setAnimSpeed(RandomFloat(-3.75f, 3.75f));

	} 
	
	/**/
	


	firstPlane.createShape();
	firstCube.createShape();
	SecondCube.createShape();
	ThirdCube.createShape();
	genericShape.createShape();

	firstPlane.setLocalPosition(Vector3D(-0.5, 0, -1.5));
	firstPlane.setLocalScale(Vector3D(8, 1, 6));
	firstPlane.setAnimSpeed(1.0f);

	firstCube.setLocalPosition(Vector3D(0, 1, 0));
	firstCube.setLocalScale(Vector3D(0.75, 0.75, 0.75));
	firstCube.setAnimSpeed(1.0f);
	
	SecondCube.setLocalPosition(Vector3D(-1.5, 2.0, 0));
	SecondCube.setLocalScale(Vector3D(0.75, 0.75, 0.75));
	SecondCube.setAnimSpeed(1.0f);

	ThirdCube.setLocalPosition(Vector3D(-1.5, 3.0, -2.0));
	ThirdCube.setLocalScale(Vector3D(0.75, 0.75, 0.75));
	ThirdCube.setAnimSpeed(1.0f);


	genericShape.setLocalPosition(Vector3D(1, 2, 1));
	genericShape.setLocalScale(Vector3D(0.25, 0.25, 0.25));
	//constant cc;
	//cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();

	//std::cout << "Create AppWindow:: " << &cc << std::endl;
	
	/*
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(this->getHWND());
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getDeviceContext());
	ImGui::StyleColorsDark();*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	

	InputSystem::get()->update();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	UIManager::getInstance()->drawAllUI();
	
	SceneCameraHandler::getInstance()->update();
	firstCube.setCamera();
	firstPlane.setCamera();
	
	//firstCube.update(EngineTime::getDeltaTime());
	

	/*
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Credits");
	
	ImGui::Text("Scene Editor V0.1\n");
	ImGui::Text("By Jacob Lo\n");
	ImGui::Text("Acknowledgements:\n");
	ImGui::Text("PardCode\n");
	ImGui::Text("Sir Neil\n");
	ImGui::SetWindowSize(ImVec2(400, 150));
	ImGui::End();
	
	ImGui::Render();
	
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
	*/
	//SecondCube.update(EngineTime::getDeltaTime());
	//ThirdCube.update(EngineTime::getDeltaTime());
	//firstPlane.update(EngineTime::getDeltaTime());
	//genericShape.update();

	/*
	for (int i = 0; i < 50; i++)
	{
		CubeArray[i].update();

	}*/
	
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	for (int i = 0; i < 100; i++)
	{
		CubeArray[i].release();
	}
	
	firstPlane.release();
	firstCube.release();
	SecondCube.release();
	ThirdCube.release();
	genericShape.release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	//SceneCameraHandler::getInstance()->sceneCameraRemoveListener();
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	//SceneCameraHandler::getInstance()->sceneCameraAddListener();
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	firstCube.RotateCube(key);
	//Camera.onKeyDown(key);
	
	if (key == 'W')
	{
		
	}
	else if (key == 'S')
	{
		
	}
	else if (key == 'A')
	{
		
	}
	else if (key == 'D')
	{
		
	} 
}


void AppWindow::onKeyUp(int key)
{
	
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	
	firstCube.scaleDownWithMouse(mouse_pos);
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	firstCube.scaleNormalWithMouse(mouse_pos);
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	firstCube.scaleUpWithMouse(mouse_pos);
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	firstCube.scaleNormalWithMouse(mouse_pos);
}

float AppWindow::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
