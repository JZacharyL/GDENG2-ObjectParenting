#pragma once
#include "Quad.h"
#include "PhysicsComponent.h"
class PhysicsCube :
    public Quad
{
public:
	PhysicsCube(String name, PrimitiveType type ,bool skipInit = false);
	~PhysicsCube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void saveEditState() override;
	void restoreEditState() override;
protected:
	float mass = 3.0f;
	PhysicsComponent* componentAttached;

};

