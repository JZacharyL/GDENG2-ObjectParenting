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

//Total time taken 4 hours
void AGameObject::setPosition(float x, float y, float z)
{
	//Save the last position before translation
	Vector3D prevPosition = localPosition;

	//Translate parent
	localPosition = Vector3D(x, y, z);

	//For all childs
	for (AGameObject* child : ChildList) {
		//Get the displacement from the childs position and the parents previous position
		Vector3D displacement = child->getLocalPosition() - prevPosition;

		//translate child position based on the parents new position and the calculated displacement value
		child->setPosition(Vector3D(x, y, z) + displacement);
	}
}

void AGameObject::setPosition(Vector3D pos)
{
	//Save the last position before translation
	Vector3D prevPosition = localPosition;

	//Translate parent
	localPosition = pos;

	//For all childs
	for (AGameObject* child : ChildList) {
		//Get the displacement from the childs position and the parents previous position
		Vector3D displacement = child->getLocalPosition() - prevPosition;

		//translate child position based on the parents new position and the calculated displacement value
		child->setPosition(pos + displacement);
	}
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

//Total time take 6 hours
void AGameObject::setScale(float x, float y, float z)
{
	Vector3D oldScale = localScale;
	localScale = Vector3D(x, y, z);

	//Distinguish which axis was actually scaled
	if (oldScale.x != localScale.x) {
		//For all childs
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D((localScale.x / oldScale.x) * child->getLocalScale().x, child->getLocalScale().y, child->getLocalScale().z);
			child->setScale(childScale);
		}
	}

	else if (oldScale.y != localScale.y) {
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D(child->getLocalScale().x, child->getLocalScale().y * (localScale.y / oldScale.y), child->getLocalScale().z);
			child->setScale(childScale);
		}
	}

	else if (oldScale.z != localScale.z) {
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D(child->getLocalScale().x, child->getLocalScale().y, (localScale.z / oldScale.z) * child->getLocalScale().z);
			child->setScale(childScale);
		}
	}
}

void AGameObject::setScale(Vector3D scale)
{
	Vector3D oldScale = localScale;
	localScale = scale;

	//Distinguish which axis was actually scaled
	if (oldScale.x != localScale.x) {
		//For all childs
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D((localScale.x / oldScale.x) * child->getLocalScale().x, child->getLocalScale().y, child->getLocalScale().z);
			child->setScale(childScale);
		}
	}

	else if (oldScale.y != localScale.y) {
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D(child->getLocalScale().x, child->getLocalScale().y * (localScale.y / oldScale.y), child->getLocalScale().z);
			child->setScale(childScale);
		}
	}

	else if (oldScale.z != localScale.z) {
		for (AGameObject* child : ChildList) {
			Vector3D childScale = Vector3D(child->getLocalScale().x, child->getLocalScale().y, (localScale.z / oldScale.z) * child->getLocalScale().z);
			child->setScale(childScale);
		}
	}
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
	Vector3D oldRot = localRotation;
	this->localRotation = rot;
	Vector3D rotDiff = localRotation - oldRot;
	
	
	//For all childs
	for (AGameObject* child : ChildList) {

		//Create A Quaternion to represent the parents rotation
		Quaternion totalRotation;

		//totalRotation = Quaternion(localRotation, )
		
		//Ensure the rotation accounts for every axis (x, y, and z)
		//Thankfully, there's no double rotations
		//Account for Rotation AROUND the x axis

		/*
		Quaternion xRot = Quaternion(Vector3D(1, 0, 0), localRotation.x);
		totalRotation *= xRot;

		
		cout << totalRotation.w << endl;

		//Account for Rotation around the y axis
		Quaternion yRot = Quaternion(Vector3D(0, 1, 0), localRotation.y);
		totalRotation *= yRot;

		cout << totalRotation.w << endl;
		*/

		//Account for Rotation around the z axis
		Quaternion zRot = Quaternion(localPosition, localRotation.z);
		totalRotation *= zRot;

		cout << totalRotation.w << endl;
		

		/*
		Vector3D dir;
		Vector3D revDiff;

		//Get the distance from the parent to the child
		Vector3D mag = child->localPosition - localPosition;
		
		//Get the angle coefficients on each axis of rotation
		//Around the z axis
		float angleX = cos(rotDiff.x);
		float angleY = sin(rotDiff.y);

		Vector3D finalDisp = mag;
		finalDisp.x = finalDisp.x * angleX;
		finalDisp.y = finalDisp.y * angleY;

		child->setPosition(finalDisp);
		*/

		//Apply rotated difference to the child position
		Vector3D initialPosition = child->getLocalPosition();
		Vector3D newPosition = Quaternion::Rotate(&initialPosition, totalRotation);

		cout << "Rotating" << endl;

		//Set the new position first
		child->setPosition(newPosition);
		
		//child->setRotation(newPosition);
		//Finally, rotate the child by the same rotation difference
		child->setRotation(rotDiff + child->getLocalRotation());
	}
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

bool AGameObject::isChild()
{
	return hasParent;
}

void AGameObject::addChild(AGameObject* newChild)
{
	ChildList.push_back(newChild);

	newChild->setParent(this);
}

AGameObject* AGameObject::getParent()
{
	//THIS IMPLEMENTATION IS PRONE TO INFINITE LOOP
	//A parent can be a child of the object that it is a parent of... so don't do that >w o
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
	if (hasParent) {
		Parent->removeChild(this);
	}

	Parent = NULL;
	hasParent = false;
}

void AGameObject::removeChild(AGameObject* child)
{
	int index = -1;
	for (int i = 0; i < ChildList.size(); i++) {
		if (ChildList[i] == child) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		ChildList.erase(ChildList.begin() + index);
	}
}

/*
Vector3D AGameObject::getPositionRecursive(float localx, float localy, float localz, AGameObject* parent)
{
	Vector3D parentVals = parent->getLocalPosition();
	Vector3D combinedVals = Vector3D(localx, localy, localz) + parentVals;

	//End case
	if (!parent->hasParent) {
		return combinedVals;
	}

	//Recursive case
	else {
		return getPositionRecursive(combinedVals.x, combinedVals.y, combinedVals.z, parent->getParent());
	}
}
*/
///Psuedocode for recursive parent checking
//Return Vector3
//position, scale, rotation = locals + parents;
//if(parent.hasParent == true) -> parent = parent.parent
//position, scale, rotation = locals + parents;
//if(parent.hasParent == false) -> done transforming