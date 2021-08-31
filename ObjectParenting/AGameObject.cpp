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

//Done after 17 hours ... now 20
void AGameObject::setRotation(float x, float y, float z)
{
	Vector3D oldRot = localRotation;
	this->localRotation = Vector3D(x, y, z);
	Vector3D rotDiff = localRotation - oldRot;

	//Account for parent object
	this->localRotation = Vector3D(x, y, z);

	//For all childs
	for (AGameObject* child : ChildList) {
		Vector3D savedPos = localPosition;
		setPosition(Vector3D(0, 0, 0));
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

		//Get the difference from the origin
		//Account for distance from origin
		//Vector3D objectDiff = child->getLocalPosition() - localPosition;
		Vector3D initialPosition;
		Vector3D newPosition;

		//Detect which axis the rotation was done over
		if (rotDiff.x != 0) {
			Quaternion xRot = Quaternion(Vector3D(1, localPosition.y, localPosition.z), rotDiff.x);

			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, xRot);
		}

		else if (rotDiff.y != 0) {
			Quaternion yRot = Quaternion(Vector3D(localPosition.x, 1, localPosition.z), rotDiff.y);
			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, yRot);
		}

		else if (rotDiff.z != 0) {
			//Account for Rotation around the z axis
			Quaternion zRot = Quaternion(Vector3D(localPosition.x, localPosition.y, 1), rotDiff.z);
			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, zRot);
		}

		//cout << totalRotation.w << endl;
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

		//cout << "Rotating" << endl;

		setPosition(savedPos);

		//Set the new position first
		child->setPosition(newPosition);

		//Finally, rotate the child by the same rotation difference
		child->setRotation(rotDiff + child->getLocalRotation());
	}
}

void AGameObject::setRotation(Vector3D rot)
{
	//Account for parent object
	
	Vector3D oldRot = localRotation;
	this->localRotation = rot;
	Vector3D rotDiff = localRotation - oldRot;
	
	//San check for quat * quat
	/*
	Quaternion q1 = Quaternion(Vector3D(0, 1, 0), 3.14 / 2);
	Quaternion q2 = Quaternion(Vector3D(1, 0, 0), 3.14 / 4);

	Quaternion result = q2 * q1;

	cout << "Result x: " << result.x << endl;
	cout << "Result y: " << result.y << endl;
	cout << "Result z: " << result.z << endl;
	cout << "Result w: " << result.w << endl;
	*/

	//San check for vector * quaternion
	/*
	Vector3D randVec = Vector3D(1, 0, 0);
	Quaternion randRot = Quaternion(Vector3D(0, 0, 1), 3.14/4);

	Vector3D result = Quaternion::Rotate(&randVec, randRot);

	cout << "Result x: " << result.x << endl;
	cout << "Result y: " << result.y << endl;
	cout << "Result z: " << result.z << endl;
	*/

	//For all childs
	for (AGameObject* child : ChildList) {
		//totalRotation = Quaternion(localRotation, )
		Vector3D savedPos = localPosition;
		setPosition(Vector3D(0, 0, 0));
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

		Vector3D initialPosition;
		Vector3D newPosition;

		//Detect which axis the rotation was done over
		if (rotDiff.x != 0) {
			Quaternion xRot = Quaternion(Vector3D(1, localPosition.y, localPosition.z), rotDiff.x);
			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, xRot);
		}

		else if (rotDiff.y != 0) {
			Quaternion yRot = Quaternion(Vector3D(localPosition.x, 1, localPosition.z), rotDiff.y);
			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, yRot);
		}

		else if (rotDiff.z != 0) {
			//Account for Rotation around the z axis
			Quaternion zRot = Quaternion(Vector3D(localPosition.x, localPosition.y, 1), rotDiff.z);
			//Apply rotated difference to the child position
			initialPosition = child->getLocalPosition();
			newPosition = Quaternion::Rotate(&initialPosition, zRot);
		}
		
		//cout << totalRotation.w << endl;
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

		//cout << "Rotating" << endl;

		//Set the new position first
		child->setPosition(newPosition);
		
		setPosition(savedPos);

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
void AGameObject::updateLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getX());
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getY());
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getZ());

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	this->localMatrix = allMatrix;
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	Matrix4x4 matrix4x4;

	matrix4x4.setManualMatrix(matrix);
	/*
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];
	*/
	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	this->overrideMatrix = true;
}

float* AGameObject::getRawMatrix()
{
	float* matrix4x4 = this->localMatrix.getMatrix();
	return matrix4x4;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getX());
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getY());
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getZ());

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrix();
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
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