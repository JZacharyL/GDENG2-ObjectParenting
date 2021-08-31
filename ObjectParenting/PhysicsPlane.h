#pragma once
#include "PhysicsCube.h"
class PhysicsPlane :
    public Quad
{
public:
	PhysicsPlane(String name, bool skipInit = false);
	~PhysicsPlane();
};

