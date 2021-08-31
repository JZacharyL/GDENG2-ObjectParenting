#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(String name, bool skipInit) : Quad(name)
{
	this->setPosition(0.0f, 5.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->updateLocalMatrix();
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));
}

PhysicsCube::~PhysicsCube()
{
	Quad::~Quad();
}

void PhysicsCube::update(float deltaTime)
{
	Quad::update(deltaTime);
}

void PhysicsCube::draw(int width, int height)
{
	Quad::draw(width, height);
}