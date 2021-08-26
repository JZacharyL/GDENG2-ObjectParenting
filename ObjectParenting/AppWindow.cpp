
#include "AppWindow.h"
#include <windows.h>
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "GameObjectManager.h"


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
	
	camera.setIdentity();
	camera.setTranslation(Vector3D(0, 0, -2.0f));

	this->m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT window = this->getClientWindowRect();
	int width = window.right - window.left;
	int height = window.bottom - window.top;

	this->m_swap_chain->init(this->m_hwnd, width, height);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vs = graphicsEngine->createVertexShader(shaderByteCode, sizeShader);
	
	srand(time(NULL));
	float x = 0.0f;//-1.25f;
	float y = 0.0f;//0.75f;
	float scale = 0.35f;

	Quad* tempQuad = new Quad("Quad", shaderByteCode, sizeShader);
	tempQuad->setAnimSpeed(1.0f);
	tempQuad->setPosition(Vector3D(0.0f, -0.0f, 1.0f));
	tempQuad->setScale(1.0f, 1.0f, 1.0f);
	//tempQuad->setRotation(Vector3D::zeros());
	//this->quadList.push_back(tempQuad);

	Plane* tempPlane = new Plane("Plane", shaderByteCode, sizeShader);
	tempPlane->setAnimSpeed(1.0f);
	tempPlane->setPosition(Vector3D(0.0f, -1.0f, 1.0f));
	tempPlane->setScale(Vector3D(5.0f, 1.0f, 5.0f));
	//tempPlane->setRotation(Vector3D::zeros());
	//this->quadList.push_back(tempPlane);
	
	graphicsEngine->releaseCompiledShader();

	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();
}


void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	
	SceneCameraHandler::get()->initialize(this->getClientWindowRect());
	this->initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	deviceContext->setVertexShader(this->m_vs);
	deviceContext->setPixelShader(this->m_ps);
	deviceContext->clearRenderTargetColor(this->m_swap_chain, 0, 0.5, 0.5, 1);

	RECT window = this->getClientWindowRect();
	int width = window.right - window.left;
	int height = window.bottom - window.top;

	deviceContext->setViewportSize(width, height);

	//Update from game manager
	GameObjectManager::getInstance()->updateAll();

	//Draw from game object manager
	GameObjectManager::getInstance()->renderAll(width, height, this->m_vs, this->m_ps);

	for(int i = 0; i < this->quadList.size(); i ++)
	{	
		this->quadList[i]->update(EngineTime::getDeltaTime());
		this->quadList[i]->draw(width, height, this->m_vs, this->m_ps);
	}


	SceneCameraHandler::get()->update();
	UIManager::getInstance()->drawAllUI();
	
	this->m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
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
