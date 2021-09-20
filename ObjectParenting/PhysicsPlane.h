#pragma once
#include "PhysicsCube.h"
class PhysicsPlane :
    public Quad
{
public:
	PhysicsPlane(String name, PrimitiveType type,bool skipInit = false);
	~PhysicsPlane();
};

