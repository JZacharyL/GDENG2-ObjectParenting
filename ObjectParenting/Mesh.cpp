#pragma once
#pragma warning(suppress : 4996)
#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"

#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>
#include <vector>

#include "GraphicsEngine.h"
#include "VertexMesh.h"
#include "ShaderLibrary.h"

Mesh::Mesh(const wchar_t* full_path): AResource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	//std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path); //THIS DOESNT WORK IN C++17 
	std::string inputfile = "NULL";
	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");


	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;


	std::cout << "Vertex List Size : " << list_vertices.size() << std::endl;
	std::cout << "Index List Size : " <<  list_indices.size() << std::endl;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		//std::cout << "Reserved Vertex List Size : " << list_vertices.size() << std::endl;
		//std::cout << "Reserved Index List Size : " << list_indices.size() << std::endl;

		
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
			//std::cout << "Loop F " << std::endl;

			
			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				//std::cout << "Loop V " << std::endl;

				
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t tx = 0.0f;
				tinyobj::real_t ty = 0.0f;
				
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];


				if (attribs.texcoords.size() > 0) {
					 tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					 ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				//std::cout << "tx: " << tx << std::endl;
				//std::cout << "ty: " << ty << std::endl;

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				
				list_indices.push_back((unsigned int)index_offset + v);
				//std::cout << "Loop V end" << std::endl;
			}

			

			index_offset += num_face_verts;
		}
		
	}

	
	
	ShaderNames shaderNames;
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	//GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);
	
	this->m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();

	this->m_vertex_buffer->load(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);

	this->m_index_buffer = GraphicsEngine::get()->createIndexBuffer();
	this->m_index_buffer->load(&list_indices[0], (UINT)list_indices.size());
	/*
	m_vertex_buffer = GraphicsEngine::get()->getRenderSys->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());
	*/

}


Mesh::~Mesh()
{
}

VertexBuffer* Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return m_index_buffer;
}
