
#include "AppWindow.h"
#include <windows.h>
#include "InputSystem.h"
#include "SceneCameraHandler.h"


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

	/*
	for(int i = 0; i < this->nQuad; i++)
	{
		/*
		if (x >= 1.0f)
		{
			x = -1.0f;
			y -= 0.25;
		}
		else
			x += 0.25f;
//

		//x = -0.75 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.75 - (-0.75))));
		//y = -0.75 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.75 - (-0.75))));
		

		Quad* tempQuad = new Quad("Quad", shaderByteCode, sizeShader);
		tempQuad->setAnimSpeed(0.5f);
		tempQuad->setPosition(Vector3D(x, y, 0.0f));
		tempQuad->setScale(Vector3D(scale, scale, scale));
		
		tempQuad->setRotation(Vector3D(1.6f, 0.0f, 0.0));
		//tempQuad->setRotation(Vector3D(45.0f, 10.0f, 10.0f));
		this->quadList.push_back(tempQuad);
	}
*/

	/*
	Vector3D rot = Vector3D(0.4f, 0.785f, 0.3f);
	Vector3D Planerot = Vector3D(0.4f, 0.785f, 0.3f);
	
	Quad* tempQuad = new Quad("Quad", shaderByteCode, sizeShader);
	tempQuad->setAnimSpeed(0.0f);
	tempQuad->setPosition(Vector3D(0.0f, -0.15f, -1.0f));
	tempQuad->setScale(scale, scale, scale);
	tempQuad->setRotation(rot);
	this->quadList.push_back(tempQuad);
	
	Quad* tempQuad1 = new Quad("Quad", shaderByteCode, sizeShader);
	tempQuad1->setAnimSpeed(0.0f);
	tempQuad1->setPosition(Vector3D(-0.25f, 0.05f, -1.0f));
	tempQuad1->setScale(scale, scale, scale);
	tempQuad1->setRotation(rot);
	this->quadList.push_back(tempQuad1);

	Quad* tempQuad2 = new Quad("Quad", shaderByteCode, sizeShader);
	tempQuad2->setAnimSpeed(0.0f);
	tempQuad2->setPosition(Vector3D(-0.45f, 0.15f, -2.0f));
	tempQuad2->setScale(scale, scale, scale);
	tempQuad2->setRotation(rot);
	this->quadList.push_back(tempQuad2);
	
	Plane* tempPlane = new Plane("Plane", shaderByteCode, sizeShader);
	tempPlane->setAnimSpeed(0.0f);
	tempPlane->setPosition(Vector3D(0.0f, -0.25f, 1.0f));
	tempPlane->setScale(Vector3D(5.0f, 1.0f, 5.0f));
	tempPlane->setRotation(Planerot);
	this->quadList.push_back(tempPlane);

	*/

	Quad* tempQuad = new Quad("Quad", shaderByteCode, sizeShader);
	tempQuad->setAnimSpeed(1.0f);
	tempQuad->setPosition(Vector3D(0.0f, -0.0f, 1.0f));
	tempQuad->setScale(1.0f, 1.0f, 1.0f);
	//tempQuad->setRotation(Vector3D::zeros());
	this->quadList.push_back(tempQuad);

	Plane* tempPlane = new Plane("Plane", shaderByteCode, sizeShader);
	tempPlane->setAnimSpeed(1.0f);
	tempPlane->setPosition(Vector3D(0.0f, -1.0f, 1.0f));
	tempPlane->setScale(Vector3D(5.0f, 1.0f, 5.0f));
	//tempPlane->setRotation(Vector3D::zeros());
	this->quadList.push_back(tempPlane);
	
	graphicsEngine->releaseCompiledShader();

	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_ps = graphicsEngine->createPixelShader(shaderByteCode, sizeShader);
	graphicsEngine->releaseCompiledShader();

}


void AppWindow::updateQuadPosition()
{
	/*
	Matrix4x4 temp;
	
	//cc.m_time = ::GetTickCount();
	
	m_delta_pos += m_delta_time / 10.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 0.15f;

	
	double time = 0;
	multiplier += increment;
	if (multiplier >= 10.0f || multiplier <= 0.0f)
		increment = -increment;

	time = EngineTime::getDeltaTime() * multiplier;
	//cc.m_time += time;

	//cc.matrix = Window::CheckInput();
	
	
	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2,2,0), m_delta_pos));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5, -1.5, 0), Vector3D(1.5,1.5,0), m_delta_pos));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(2,2,0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//
	//cc.m_world *= temp;

	/*
	cc.m_world.setScale(Vector3D(1, 1, 1));

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world *= temp;
	//

	cc.m_world.setIdentity();
	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);
	
	for (int i = 0; i < nQuad; i++)
	{
		QuadList[i].getCB()->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
		QuadList[i].update();
	}
	*/
}


void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->ShowCursor(true);
	
	SceneCameraHandler::get()->initialize(this->getClientWindowRect());
	this->initialize();
	/*
	GraphicsEngine::get()->init();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	vertex list[] = 
	{
		//X - Y - Z
		{Vector3D(-0.75f,-0.75f,0.0f),	Vector3D(1,0,0),		Vector3D(0,0,0)}, // POS1
		{Vector3D(-0.75f,-0.25f,0.0f),	Vector3D(0,1,0),		Vector3D(1,0,0)}, // POS2
		{Vector3D(-0.25f,-0.75f,0.0f),	Vector3D(0,0,1),		Vector3D(0,1,0)}, // POS3
		{Vector3D(-0.25f,-0.25f,0.0f),	Vector3D(0,0,0),		Vector3D(0,0,1)},
	};

	vertex list1[] =
	{
		//X - Y - Z
		{Vector3D(0.75f,0.75f,0.0f),	Vector3D(0,0,1),		Vector3D(0,0,0)}, // POS1
		{Vector3D(0.75f,0.25f,0.0f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(0.25f,0.75f,0.0f),	Vector3D(1,0,0),		Vector3D(0,1,0)}, // POS3
		{Vector3D(0.25f,0.25f,0.0f),	Vector3D(0,0,0),		Vector3D(1,0,0)},

	};

	vertex list2[] =
	{
		//X - Y - Z
		{Vector3D(-0.75f,0.25f,0.0f),	Vector3D(0,0,0),		Vector3D(1,0,0)}, // POS1
		{Vector3D(-0.75f,0.75f,0.0f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(-0.25f,0.25f,0.0f),	Vector3D(0,0,1),		Vector3D(0,1,0)}, // POS3
		{Vector3D(-0.25f,0.75f,0.0f),	Vector3D(1,0,0),		Vector3D(0,0,0)},

	};

	vertex list0[] =
	{
		//X - Y - Z
		{Vector3D(-0.75f,-0.75f,0.0f),	Vector3D(0,0,0),		Vector3D(1,0,0)}, // POS1
		{Vector3D(-0.75f,0.25f,0.0f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(0.25f,-0.5f,0.0f),	Vector3D(0,0,1),		Vector3D(0,1,0)}, // POS3
		{Vector3D(0.0f,0.25f,0.0f),		Vector3D(1,0,0),		Vector3D(0,0,0)},

	};

	vertex list4[] =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.75f,0.0f),	Vector3D(1,0,0),		Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.45f,0.0f,0.0f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(0.45f,-0.5f,0.0f),	Vector3D(0,0,1),		Vector3D(1,0,0)}, // POS3
		{Vector3D(-0.5f,-0.5f,0.0f),	Vector3D(0,0,0),		Vector3D(0,0,0)},
								  
	};

	vertex list5[] =
	{
		//X - Y - Z
		{Vector3D(-0.25f,-0.25f,0.0f),	Vector3D(1,0,0),		Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.25f,0.25f,0.0f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(0.25f,-0.25f,0.0f),	Vector3D(0,0,1),		Vector3D(1,0,0)}, // POS3
		{Vector3D(0.25f,0.25f,0.0f),	Vector3D(0,0,0),		Vector3D(0,0,0)},

	};

	vertex Cube[] =
	{
		{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D(1,0,0),		Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.5f,0.5f,-0.5f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(0.5f,0.5f,-0.5f),	Vector3D(0,0,1),		Vector3D(1,0,0)}, // POS3
		{Vector3D(0.5f,-0.5f,-0.5f),	Vector3D(0,0,0),		Vector3D(0,0,0)},

		{Vector3D(0.5f,-0.5f,0.5f),	Vector3D(1,0,0),		Vector3D(0,1,0)}, // POS1
		{Vector3D(0.5f,0.5f,0.5f),	Vector3D(0,1,0),		Vector3D(0,0,1)}, // POS2
		{Vector3D(-0.5f,0.5f,0.5f),	Vector3D(0,0,1),		Vector3D(1,0,0)}, // POS3
		{Vector3D(-0.5f,-0.5f,0.5f),	Vector3D(0,0,0),		Vector3D(0,0,0)},
	};

	
	
	Quad* quad1 = new Quad();
	quad1->updateMatrix(Cube);
	quad1->init(rc, m_hwnd);
	QuadList[nQuad] = *quad1;
	nQuad++;
	
	/*
	Quad* quad1 = new Quad();
	quad1->updateMatrix(list);
	quad1->init(rc, m_hwnd);
	QuadList[nQuad] = *quad1;
	nQuad++;

	
	Quad* quad2 = new Quad();
	quad2->updateMatrix(list1);
	quad2->init(rc, m_hwnd);
	QuadList[nQuad] = *quad2;
	nQuad++;

	Quad* quad3 = new Quad();
	quad3->updateMatrix(list2);
	quad3->init(rc, m_hwnd);
	QuadList[nQuad] = *quad3;
	nQuad++;
	//
	cc.m_time = 0;
	*/
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

	/*/
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	
	Matrix4x4 temp;
	temp.setIdentity();
	temp.setRotationX(delta_rot_x);
	worldCam *= temp;
	temp.setIdentity();
	temp.setRotationY(delta_rot_y);
	worldCam *= temp;

	Vector3D newPos = camera.getTranslation() + worldCam.getZDirection() * (forward * 0.01f);
	newPos = newPos + worldCam.getXDirection() * (right * 0.01f);
	
	worldCam.setTranslation(newPos);
	camera = worldCam;
	worldCam.inverse();
	*/

	for(int i = 0; i < this->quadList.size(); i ++)
	{	
		this->quadList[i]->update(EngineTime::getDeltaTime());
		this->quadList[i]->draw(width, height, this->m_vs, this->m_ps);
	}


	SceneCameraHandler::get()->update();
	UIManager::getInstance()->drawAllUI();
	
	this->m_swap_chain->present(true);
	
	/*
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	updateQuadPosition();


	m_swap_chain->present(true);
	*/
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

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
	/*
	if(key == 'W')
	{
		//delta_rot_x += rotSpeed * EngineTime::getDeltaTime();
		forward = 1.0f;
	}
	else if(key == 'S')
	{
		//delta_rot_x -= rotSpeed * EngineTime::getDeltaTime();
		forward = -1.0f;
	}
	else if(key == 'D')
	{
		//delta_rot_y += rotSpeed * EngineTime::getDeltaTime();
		right = 1.0f;
	}
	else if(key == 'A')
	{
		//delta_rot_y -= rotSpeed * EngineTime::getDeltaTime();
		right = -1.0f;
	}
	*/
}

void AppWindow::onKeyUp(int key)
{
	//forward = 0.0f;
	//right = 0.0f;
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
