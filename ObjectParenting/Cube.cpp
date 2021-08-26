#include "Cube.h"

#include "SceneCameraHandler.h"

Cube::Cube()
{

}

Cube::~Cube()
{
}

void Cube::createShape()
{
	
	vertex updatedlist[8] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0.8,0.8,0.8),  Vector3D(0.8,0.8,0.8) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0.8,0.8,0.8), Vector3D(0.8,0.8,0.8) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0.8,0.8,0.8),  Vector3D(0.8,0.8,0.8) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(0.8,0.8,0.8), Vector3D(0.8,0.8,0.8) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0.8,0.8,0.8), Vector3D(0.8,0.8,0.8) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0.8,0.8,0.8), Vector3D(0.8,0.8,0.8) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0.8,0.8,0.8),  Vector3D(0.8,0.8,0.8) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0.8,0.8,0.8), Vector3D(0.8,0.8,0.8) }



		
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(updatedlist);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(updatedlist, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void Cube::update(float deltatime)
{
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	constant cc;
	cc.m_angle = m_angle;

	//this->setCamera();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);


}

void Cube::release()
{
	this->m_vb->release();
	this->m_ib->release();
	this->m_vs->release();
	this->m_ps->release();
}

void Cube::updateQuadPosition(Vector3D position, Vector3D scale, float animspeed)
{
	constant cc;
	cc.m_time = 1.0;

	m_delta_pos += EngineTime::getDeltaTime() / 2.0f;
	if (m_delta_pos > 1.0f) {
		m_delta_pos = 0;
	}

	Matrix4x4 temp;

	m_delta_scale += EngineTime::getDeltaTime() / animspeed;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f)); // Setting scale when using 2d

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos)); // setting translation using 2d

	//cc.m_world *= temp;

	//SCALE->Rotate->Transform

	//cc.m_world.setScale(scale);
	cc.m_world.setIdentity();

	cc.m_world.setScale(Vector3D(m_mouses_scale, m_mouses_scale, m_mouses_scale));
	
	temp.setIdentity();
	temp.setRotationZ(m_delta_scale); //adding Rotation animation 
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(position);
	cc.m_world *= temp;
	


	cc.m_view.setIdentity();
	
	cc.m_proj.setOrthoLH
	(
		//(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f
		(1004 - 0) / 400.0f,
		//(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		(725 - 0) / 400.0f,
		-1.0f,
		1.0f
	);
	//cc.m_proj.setPerspectiveFovLH(2.0f, ((float)(1004 - 0) / (float)(725 - 0) ), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::setCamera()
{
	constant cc;
	Matrix4x4 temp;
	cc.m_time = 1.0;

	m_delta_scale += EngineTime::getDeltaTime() / this->getAnimSpeed();
	
	cc.m_world.setIdentity();
	cc.m_view.setIdentity();
	
	cc.m_world.setScale(this->getLocalScale());

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(1.5f, 1.5f, 0.0f), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//cc.m_world.setScale(Vector3D(m_mouses_scale, m_mouses_scale, m_mouses_scale));
	//cc.m_world *= temp;
	
	temp.setIdentity();
	//temp.setRotationZ(m_delta_scale); //adding Rotation animation 
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	cc.m_world *= temp;

	Matrix4x4 cameraMatrix;
	cameraMatrix.setIdentity();
	cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	
	cc.m_view = cameraMatrix;
	
	/*cc.m_proj.setOrthoLH
	(
		//(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f
		(1004 - 0) / 400.0f,
		//(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		(725 - 0) / 400.0f,
		-1.0f,
		100.0f
	);*/
	
	
	//cc.m_view = Camera;
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)(1004 - 0) / (float)(725 - 0) ), 0.1f, 100.0f);  //first value is Bigger = wider

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::RotateCube(int key)
{
	constant cc;
	if (key == 'I')
	{
		
		std::cout << "pressed I" << std::endl;
		//m_rot_x += 3.14f * EngineTime::getDeltaTime();

		cc.m_proj.setOrthoLH
		(
			//(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f
			(1004 - 0) / 400.0f,
			//(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
			(725 - 0) / 400.0f,
			-1.0f,
			1.0f
		);
		//cc.m_proj.setPerspectiveFovLH(2.0f, ((float)(1004 - 0) / (float)(725 - 0) ), 0.1f, 100.0f);

		m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	}
	else if (key == 'J')
	{
		//m_rot_x -= 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'K')
	{
		m_rot_y += 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'L')
	{
		m_rot_y -= 3.14f * EngineTime::getDeltaTime();
	}

}

void Cube::RotateCubeMouse(const Point& delta_mouse_pos)
{
	m_rot_x -= delta_mouse_pos.m_y * EngineTime::getDeltaTime();
	m_rot_y -= delta_mouse_pos.m_x * EngineTime::getDeltaTime();
}

void Cube::scaleUpWithMouse(const Point& delta_mouse_pos)
{
	m_mouses_scale = 0.75f;
}

void Cube::scaleDownWithMouse(const Point& delta_mouse_pos)
{
	m_mouses_scale = 0.5f;
}

void Cube::scaleNormalWithMouse(const Point& delta_mouse_pos)
{
	m_mouses_scale = 0.25f;
}
