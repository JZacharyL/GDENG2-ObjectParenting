#pragma once
#include <Windows.h>
#include <DirectXMath.h>

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	bool init();
	void update(RAWINPUT* raw);
	DirectX::XMMATRIX CheckKeyCode();

private:
	float scale_x = 1;
	float scale_y = 1;
	float scale_z = 1;
};

