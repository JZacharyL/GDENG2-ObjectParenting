
#pragma once
#include "Mesh.h"
#include "ResourceManager.h"

class MeshManager: public AResourceManager
{
public:
	
	static void initialize();
	static void destroy();
	static MeshManager* getInstance();
	Mesh* createMeshFromFile(const wchar_t* file_path);
protected:
	static MeshManager* sharedInstance;
	MeshManager();
	~MeshManager();
	virtual AResource* createResourceFromFileConcrete(const wchar_t* file_path);

	AResource* convertToResource(const wchar_t* filePath);

};

