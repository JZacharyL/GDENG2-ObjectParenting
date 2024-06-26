#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{
		
	}

	~InputListener()
	{

	}

	//Keyboard
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//Mouse
	virtual void onMouseMove(const Point& deltaMousePos) = 0;
	virtual void onLeftMouseDown(const Point& deltaMousePos) = 0;
	virtual void onLeftMouseUp(const Point& deltaMousePos) = 0;
	virtual void onRightMouseDown(const Point& deltaMousePos) = 0;
	virtual void onRightMouseUp(const Point& deltaMousePos) = 0;
};