#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"
#include <iostream>
PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	//whenever a new physics component is initialized. Register to physics system
	//std::cout << "registering component" << std::endl;
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);

	//std::cout << "done registering component" << std::endl;
	//std::cout << "creating physics common" << std::endl;
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	//std::cout << "done creating physics common" << std::endl;
	//std::cout << "creating physics World" << std::endl;
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
	//std::cout << "done creating physics World" << std::endl;
	
	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform;
	//transform.setToIdentity();
	//transform.setPosition(this->getOwner()->getPhysicsLocalMatrix());
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix()); //Problematic sector
	//std::cout << "creating Box shape" << std::endl;
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.getX() / 2, scale.getY() / 2, scale.getZ() / 2)); //half extent
	//std::cout << "done creating Box shape" << std::endl;

	//std::cout << "creating RigidBody" << std::endl;
	this->rigidBody = physicsWorld->createRigidBody(transform);
	//transform.setToIdentity();
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);
	//std::cout << "done creating Box shape" << std::endl;
	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	AComponent::~AComponent();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}