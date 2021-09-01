
#include "AppWindow.h"
#include <windows.h>
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "ShaderLibrary.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::initialize()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();

	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT window = this->getClientWindowRect();
	int width = window.right - window.left;
	int height = window.bottom - window.top;
	
	std::cout << "creating shaderLibrary" << endl;
	TextureManager::initialize();
	MeshManager::initialize();
	ShaderLibrary::initialize();
	BaseComponentSystem::initialize();
	/*
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	*/
	std::cout << "done creating shaderLibrary" << endl;
	
	
	camera.setIdentity();
	camera.setTranslation(Vector3D(0, 0, -2.0f));

	

	this->m_swap_chain->init(this->m_hwnd, width, height);

	GameObjectManager::initialize();
	SceneCameraHandler::get()->initialize(this->getClientWindowRect());
	
	srand(time(NULL));
	float x = 0.0f;//-1.25f;
	float y = 0.0f;//0.75f;
	float scale = 0.35f;


}


void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	
	
	this->initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	//deviceContext->setVertexShader(this->m_vs);
	//deviceContext->setPixelShader(this->m_ps);
	ShaderNames shaderNames;
	deviceContext->clearRenderTargetColor(this->m_swap_chain, 0, 0.5, 0.5, 1);

	RECT window = this->getClientWindowRect();
	int width = window.right - window.left;
	int height = window.bottom - window.top;

	deviceContext->setViewportSize(width, height);

	
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	//Update from game manager
	GameObjectManager::getInstance()->updateAll();

	//Draw from game object manager
	GameObjectManager::getInstance()->renderAll(width, height);
	/*
	for(int i = 0; i < this->quadList.size(); i ++)
	{	
		this->quadList[i]->update(EngineTime::getDeltaTime());
		this->quadList[i]->draw(width, height);
	}
	*/

	SceneCameraHandler::get()->update();
	UIManager::getInstance()->drawAllUI();
	
	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	//m_vs->release();
	//m_ps->release();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	
}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Point& deltaMousePos)
{
	//RECT window = this->getClientWindowRect();
	//int width = window.right - window.left;
	//int height = window.bottom - window.top;
	
	//delta_rot_x += (deltaMousePos.y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	//delta_rot_y += (deltaMousePos.x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	//InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::onLeftMouseDown(const Point& deltaMousePos)
{
	delta_Scale = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& deltaMousePos)
{
	delta_Scale = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& deltaMousePos)
{
	delta_Scale = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& deltaMousePos)
{
	delta_Scale = 1.0f;
}
