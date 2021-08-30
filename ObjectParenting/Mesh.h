
#pragma once
#include "AResource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Mesh: public AResource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	VertexBuffer* getVertexBuffer();
    IndexBuffer* getIndexBuffer();
private:
	VertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
private:
	friend class DeviceContext;
};

