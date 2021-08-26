#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D::ones();
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	//Account for parent object
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	//Account for parent object
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	//Account for parent object
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	//Account for parent object
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	//Account for parent object
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	//Account for parent object
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

string AGameObject::getName()
{
	return this->name;
}

void AGameObject::setName(string newName)
{
	name = newName;
}

bool AGameObject::isEnabled()
{
	return enabled;
}

void AGameObject::setEnabled(bool state)
{
	enabled = state;
}

AGameObject* AGameObject::getParent()
{
	if (!hasParent) {
		cout << "Call to null parent made" << endl;
	}
	return Parent;
}

void AGameObject::setParent(AGameObject* newParent)
{
	Parent = newParent;
	hasParent = true;
}

void AGameObject::unsetParent()
{
	Parent = NULL;
	hasParent = false;
}

///Psuedocode for recursive parent checking
//Return Vector3
//position, scale, rotation = locals + parents;
//if(parent.hasParent == true) -> parent = parent.parent
//position, scale, rotation = locals + parents;
//if(parent.hasParent == false) -> done transforming