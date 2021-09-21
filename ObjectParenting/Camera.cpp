#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"

Camera::Camera(std::string name, PrimitiveType type) : AGameObject(name, type)
{
	InputSystem::get()->addListener(this);

	this->view = View::Perspective;

	this->setPosition(Vector3D(0, 0, -2.0f));
	this->updateViewMatrix();
}

Camera::~Camera()
{
	InputSystem::get()->removeListener(this);
}

void Camera::initialize(RECT window)
{
	this->width = window.right - window.left;
	this->height = window.bottom - window.top;
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();
	float moveSpeed = 5.0f;

	if (InputSystem::get()->isKeyDown('W')) {
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('S')) {
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('D')) {
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	else if (InputSystem::get()->isKeyDown('A')) {
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}

	else if (InputSystem::get()->isKeyDown('E')) {
		y += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
	
	else if (InputSystem::get()->isKeyDown('Q')) {
		y -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::draw(int width, int height)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getX());
	worldCam = worldCam.multiplyTo(temp);

	temp.setRotationY(localRot.getY());
	worldCam = worldCam.multiplyTo(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	worldCam.inverse();
	this->localMatrix = worldCam;


	
}

Camera::View Camera::getView()
{
	return this->view;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
	/*
	if (key == 'C') {
		if (this->view == View::Perspective)
		{
			this->view = View::Orthographic;
		}
		else
		{
			this->view = View::Perspective;
		}
	}
	*/
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& deltaMousePos)
{
	InputSystem::get()->ShowCursor(true);
	//If mouse is down
	
	if (this->mouseDown) {
		//InputSystem::get()->ShowCursor(false);
		//Get local values of camera
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.getX();
		float y = localRot.getY();
		float z = localRot.getZ();

		//Set pan speed
		float speed = 0.1f;

		//Get displacement from difference of X and Y rotations
		x += (deltaMousePos.y - (this->height / 2.0f)) * EngineTime::getDeltaTime() * speed;
		y += (deltaMousePos.x - (this->width / 2.0f)) * EngineTime::getDeltaTime() * speed;
		
		//Set new rotation based on mouse
		this->setRotation(x, y, z);

		//Update the view frustrum
		this->updateViewMatrix();

		//Re-center mouse
		InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
	}
	/*
	if (this->mouseDown) {
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.getX();
		float y = localRot.getY();
		float z = localRot.getZ();

		float speed = 0.1f;
		x += deltaMousePos.y * speed;
		y += deltaMousePos.x * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();

		std::cout << " Local rot: " << this->getLocalRotation().getX() << " " << this->getLocalRotation().getY() << " " << this->getLocalRotation().getZ() << "\n";
	}*/
}

void Camera::onLeftMouseDown(const Point& deltaMousePos)
{
	
}

void Camera::onLeftMouseUp(const Point& deltaMousePos)
{
}

void Camera::onRightMouseDown(const Point& deltaMousePos)
{
	//InputSystem::get()->ShowCursor(false);
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point& deltaMousePos)
{
	//InputSystem::get()->ShowCursor(true);
	this->mouseDown = false;
}
