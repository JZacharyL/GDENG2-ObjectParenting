#include "InputSystem.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}

void InputSystem::update()
{
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	if(firstTime)
	{
		oldMousePos = Point(currentMousePos.x, currentMousePos.y);
		firstTime = false;
	}

	if(currentMousePos.x != oldMousePos.x && currentMousePos.y != oldMousePos.y)
	{
		std::unordered_set<InputListener*>::iterator it = SetListener.begin();

		while (it != SetListener.end())
		{
			(*it)->onMouseMove(Point(currentMousePos.x, currentMousePos.y));
			++it;
		}
	}
	oldMousePos = Point(currentMousePos.x, currentMousePos.y);
	
	if(::GetKeyboardState(keysState))
	{
		for(unsigned int i = 0; i < 256; i++)
		{
			//Key is down
			if(keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = SetListener.begin();

				while (it != SetListener.end())
				{
					if(i == VK_LBUTTON)
					{
						if(keysState[i] != oldKeysState[i])
							(*it)->onLeftMouseDown(Point(currentMousePos.x, currentMousePos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onRightMouseDown(Point(currentMousePos.x, currentMousePos.y));
					}
					else
					{
						if (keysState[i] != oldKeysState[i])
							(*it)->onKeyDown(i);
					}
					
					++it;
				}
			}

			//Key is up
			else
			{
				if(keysState[i] != oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = SetListener.begin();

					while (it != SetListener.end())
					{
						if(i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Point(currentMousePos.x, currentMousePos.y));

						else if(i == VK_RBUTTON)
							(*it)->onRightMouseUp(Point(currentMousePos.x, currentMousePos.y));
						else
							(*it)->onKeyUp(i);
						
						++it;
					}
				}
			}
		}

		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	SetListener.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	SetListener.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::ShowCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	for (unsigned int i = 0; i < 256; i++)
	{
		if(i == key)
		{
			if (keysState[i] & 0x80)
				return true;
			
			else
				return false;
		}
	}

	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (unsigned int i = 0; i < 256; i++)
	{
		if (i == key)
		{
			if (!(keysState[i] & 0x80))
				return true;

			else
				return false;
		}
	}

	return false;
}
