#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	static InputSystem* get();

	void update();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void ShowCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);
	
private:
	std::unordered_set<InputListener*> SetListener;
	unsigned char keysState[256] = {};
	unsigned char oldKeysState[256] = {};

	Point oldMousePos;
	bool firstTime = true;
};

