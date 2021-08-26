#include "AGameObject.h"
#include <iostream>


AGameObject::AGameObject()
{
	LocalScale = Vector3D::Ones();
	LocalPosition = Vector3D::Zeros();
	LocalRotation = Vector3D::Zeros();
	AnimationSpeed = 1.0f;
}

AGameObject::~AGameObject()
{

	
}



void AGameObject::setLocalPosition(Vector3D position)
{
	LocalPosition = position;
}

void AGameObject::setLocalScale(Vector3D scale)
{
	LocalScale = scale;
}

void AGameObject::setLocalRotation(Vector3D rotation)
{
	LocalRotation = rotation;
}

void AGameObject::setAnimSpeed(float speed)
{
	AnimationSpeed = speed;
}


Vector3D AGameObject::getLocalPosition()
{
	return this->LocalPosition;
}

Vector3D AGameObject::getLocalScale()
{
	return this->LocalScale;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->LocalRotation;
}

float AGameObject::getAnimSpeed()
{
	return this->AnimationSpeed;
}
