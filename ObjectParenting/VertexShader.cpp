#include "VertexShader.h"


#include <iostream>

#include "GraphicsEngine.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

void VertexShader::release()
{
	m_vs->Release();
	delete this;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, NULL, &m_vs))) {
		std::cout << "vs init failed in VertexShader class!!" << std::endl;
		return false;
	}
	return true;
}
