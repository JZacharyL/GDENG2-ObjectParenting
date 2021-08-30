#include "ShaderLibrary.h"
#include "AUIScreen.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GameObjectManager.h"
ShaderLibrary * ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL) {
		std::cout << "Vertex shader " << vertexShaderName.c_str() << " not found. Have you initialized it? \n";
		//std::cout << "Vertex shader " << " not found. Have you initialized it? \n";
	}
	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "Pixel shader " << pixelShaderName.c_str() << " not found. Have you initialized it? \n";
		//std::cout << "Pixel shader "  << " not found. Have you initialized it? \n";
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	//initialize and load all shaders for use
	GraphicsEngine* graphEngine = GraphicsEngine::get();

	ShaderNames shaderNames;
	ShaderData shaderData;

	
	//void* shaderByteCode = nullptr;
	//size_t sizeShader = 0;
	//std::cout << "Compiling Vertex shaderLibrary" << std::endl;
	graphEngine->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//std::cout << "Done Compiling Vertex shaderLibrary" << std::endl;

	//std::cout << "Compiling Pixel shaderLibrary" << std::endl;
	graphEngine->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//std::cout << "Done Compiling Pixel shaderLibrary" << std::endl;

	//std::cout << "Compiling textured Vertex shaderLibrary" << std::endl;
	graphEngine->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//std::cout << "Done Compiling textured Vertex shaderLibrary" << std::endl;

	//std::cout << "Compiling textured Pixel shaderLibrary" << std::endl;
	graphEngine->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//std::cout << "done Compiling textured Pixel shaderLibrary" << std::endl;


	//std::cout << "Compiling textured Vertex shaderLibrary" << std::endl;
	graphEngine->compileVertexShader(shaderNames.OBJECT_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.OBJECT_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);
	//std::cout << "Done Compiling textured Vertex shaderLibrary" << std::endl;
	
	std::cout << "Shader library initialized. \n";
}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME]->release();

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}