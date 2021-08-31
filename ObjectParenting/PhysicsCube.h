#pragma once
#include "Quad.h"
class PhysicsCube :
    public Quad
{
public:
	PhysicsCube(String name, bool skipInit = false);
	~PhysicsCube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

protected:
	float mass = 3.0f;
};

