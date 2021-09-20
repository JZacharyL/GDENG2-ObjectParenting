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
#include "EditorAction.h"
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

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!" << std::endl;
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
		String revisedString = gameObject->getName() + "(" + std::to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != NULL) {
			count++;
			revisedString = gameObject->getName() + "(" + std::to_string(count) + ")";
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

void GameObjectManager::createObject(AGameObject::PrimitiveType type)
{
	std::cout << "Object generation call received" << std::endl;
	if (type == AGameObject::PrimitiveType::CUBE) {
		std::cout << "Cube creation order parsed" << std::endl;
		Quad* cube = new Quad("Cube", type);
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	if (type == AGameObject::PrimitiveType::PLANE) {
		std::cout << "Plane creation order parsed" << std::endl;
		Plane* plane = new Plane("Plane", type);
		this->addObject(plane);
	}

	if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		std::cout << "Textured Cubecreation order parsed" << std::endl;
		TexturedCube* tex_Cube = new TexturedCube("TexturedCube1", type);
		tex_Cube->setPosition(0.0f, 0.0f, 0.0f);
		tex_Cube->setScale(1.0f, 1.0f, 1.0f);
		
		this->addObject(tex_Cube);
	}

	if (type == AGameObject::PrimitiveType::TEAPOT) {
		std::cout << "Textured Teapot order parsed" << std::endl;
		Teapot* Potter = new Teapot("Teapot", type);
		this->addObject(Potter);
		
	}

	if (type == AGameObject::PrimitiveType::BUNNY) {
		std::cout << "Textured BUNNY order parsed" << std::endl;
		Bunny* Pekora = new Bunny("Bunny", type);
		std::cout << "Textured BUNNY order Created" << std::endl;
		this->addObject(Pekora);

	}
	if (type == AGameObject::PrimitiveType::ARMADILLO) {
		std::cout << "Textured ARMADILLO order parsed" << std::endl;
		Armadillo* Bob = new Armadillo("Armadillo", type);
		this->addObject(Bob);
	}

	if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		std::cout << "Physics Cube order parsed" << std::endl;
		for (int i = 0; i < 5; i++) {
			PhysicsCube* pCube = new PhysicsCube("PCube", type);
			this->addObject(pCube);
		}
	}
	if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		std::cout << "Physics Plane order parsed" << std::endl;
		PhysicsPlane* pPlane = new PhysicsPlane("PPLane", type);
		this->addObject(pPlane);

	}
}

void GameObjectManager::createObjectFromFile(String name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale)
{
	if (type == AGameObject::PrimitiveType::CUBE) {
		Quad* cube = new Quad(name, type);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane(name, type);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
	}

	else if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(name, type);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube(name, type);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(name, type);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
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

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	//	~object();
	}
}

void GameObjectManager::setSelectedObject(std::string name)
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

void GameObjectManager::saveEditStates()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->restoreEditState();
	}
}

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());
	if (object != NULL) {
		//re-apply state
		object->setLocalMatrix(action->getStoredMatrix().getMatrix());
		object->setPosition(action->getStorePos());
		object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
		object->setScale(action->getStoredScale());

	}
}

