#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "AComponent.h"
#include <iostream>
#include <vector>
#include "reactphysics3d/reactphysics3d.h"


using namespace std;

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	double m_time;
};

class VertexShader;
class PixelShader;

class AGameObject
{
public:

	struct AQuaternion {
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	
	AGameObject(string name);
	~AGameObject();

	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	//void move(float x, float y, float z);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	void setRotation(float x, float y, float z, float w);//added from sir
	Vector3D getLocalRotation();

	string getName();
	void setName(string newName);

	bool isEnabled();
	void setEnabled(bool state);

	bool isChild();
	void addChild(AGameObject* newChild);
	AGameObject* getParent();
	
	void unsetParent();
	void removeChild(AGameObject* child);
	
	void updateLocalMatrix(); //updates local matrix based from latest position, rotation, and scale.
	void setLocalMatrix(float matrix[16]);
	float* getRawMatrix();
	float* getPhysicsLocalMatrix(); //scale is set to 1.0

	friend class GameObjectManager;

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentOfType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

protected:
	void setParent(AGameObject* newParent);
	bool hasParent;
	AGameObject* Parent;

	string name;
	bool enabled = true;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D relativeScale = Vector3D::ones();
	//Vector3D localRotation = Vector3D::zeros();
	Matrix4x4 localMatrix;

	AQuaternion orientation;


	bool overrideMatrix = false;

	ComponentList componentList;
	//Parent checking
	//Vector3D getPositionRecursive(float localx, float localy, float localz, AGameObject* parent);

	vector<AGameObject*> ChildList;
};