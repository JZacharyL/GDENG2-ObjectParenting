#include "GameObjectManager.h"
#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Quad.h"
#include "Plane.h"
#include "TexturedCube.h"
#include "Teapot.h"
#include "Bunny.h"
#include "AGameObject.h"
#include "Armadillo.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	sharedInstance->gameObjectMap.clear();
	sharedInstance->gameObjectList.clear();
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(string name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!" << endl;
		return NULL;
	}
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->update(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->draw(viewportWidth, viewportHeight);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	if (this->gameObjectMap[gameObject->getName()] != NULL) {
		int count = 1;
		String revisedString = gameObject->getName() + "(" + to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != NULL) {
			count++;
			revisedString = gameObject->getName() + "(" + to_string(count) + ")";
		}
		//std::cout << "Duplicate found. New name is: " << revisedString << "\n";
		gameObject->setName(revisedString);
		this->gameObjectMap[revisedString] = gameObject;
	}

	else {
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}

	this->gameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	cout << "Object generation call received" << endl;
	if (type == PrimitiveType::CUBE) {
		cout << "Cube creation order parsed" << endl;
		Quad* cube = new Quad("Cube");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	if (type == PrimitiveType::PLANE) {
		cout << "Plane creation order parsed" << endl;
		Plane* plane = new Plane("Plane");
		this->addObject(plane);
	}

	if (type == PrimitiveType::TEXTURED_CUBE) {
		cout << "Textured Cubecreation order parsed" << endl;
		TexturedCube* tex_Cube = new TexturedCube("TexturedCube1");
		tex_Cube->setPosition(0.0f, 0.0f, 0.0f);
		tex_Cube->setScale(1.0f, 1.0f, 1.0f);
		
		this->addObject(tex_Cube);
	}

	if (type == PrimitiveType::TEAPOT) {
		cout << "Textured Teapot order parsed" << endl;
		Teapot* Potter = new Teapot("Teapot");
		this->addObject(Potter);
		
	}

	if (type == PrimitiveType::BUNNY) {
		cout << "Textured BUNNY order parsed" << endl;
		Bunny* Pekora = new Bunny("Bunny");
		cout << "Textured BUNNY order Created" << endl;
		this->addObject(Pekora);

	}
	if (type == PrimitiveType::ARMADILLO) {
		cout << "Textured ARMADILLO order parsed" << endl;
		Armadillo* Bob = new Armadillo("Armadillo");
		this->addObject(Bob);
	}

	if (type == PrimitiveType::PHYSICS_CUBE) {
		cout << "Physics Cube order parsed" << endl;
		PhysicsCube* pCube = new PhysicsCube("PCube");
		this->addObject(pCube);

	}
	if (type == PrimitiveType::PHYSICS_PLANE) {
		cout << "Physics Plane order parsed" << endl;
		PhysicsPlane* pPlane = new PhysicsPlane("PPLane");
		this->addObject(pPlane);

	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::deleteObjectByName(string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(string name)
{
	if (this->gameObjectMap[name] != NULL) {
		this->setSelectedObject(this->gameObjectMap[name]);
	}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}

