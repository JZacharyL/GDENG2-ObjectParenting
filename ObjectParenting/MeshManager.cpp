

#include "MeshManager.h"
#include "Mesh.h"
#include <filesystem>
#include <experimental/filesystem>
#include <iostream>

MeshManager* MeshManager::sharedInstance = NULL;



void MeshManager::initialize()
{
	sharedInstance = new MeshManager();
}

void MeshManager::destroy()
{
	delete sharedInstance;
}

MeshManager* MeshManager::getInstance()
{
	return sharedInstance;
}


MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
}

Mesh* MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	std::cout << "Create mesh from file called" << std::endl;
	std::wstring fullPath = std::experimental::filesystem::absolute(file_path);

	if (this->resourceMap[fullPath] == NULL) {
		this->resourceMap[fullPath] = this->createResourceFromFileConcrete(file_path);
	}

	std::cout << "returning mesh" << std::endl;
	return (Mesh*)this->resourceMap[fullPath];
}
AResource * MeshManager::createResourceFromFileConcrete(const wchar_t * file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		std::cout << "Creating mesh in Mesh Manager" << std::endl;
		mesh = new Mesh(file_path);
		std::cout << "Done Creating mesh in Mesh Manager" << std::endl;
	}
	catch (...) {}

	return mesh;
}

