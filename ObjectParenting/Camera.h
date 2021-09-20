#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include <Windows.h>



class Camera : public AGameObject, public InputListener
{
public:
	enum View
	{
		Perspective,
		Orthographic
	};
	
	Camera(std::string name, PrimitiveType type);
	~Camera();

	void initialize(RECT window);
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void updateViewMatrix();
	View getView();
	Matrix4x4 getViewMatrix();

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& deltaMousePos) override;

	virtual void onLeftMouseDown(const Point& deltaMousePos) override;
	virtual void onLeftMouseUp(const Point& deltaMousePos) override;
	virtual void onRightMouseDown(const Point& deltaMousePos) override;
	virtual void onRightMouseUp(const Point& deltaMousePos) override;

private:
	View view;
	bool mouseDown = false;
	float width = 0;
	float height = 0;
};

