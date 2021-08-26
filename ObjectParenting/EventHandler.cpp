#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::init()
{
	RAWINPUTDEVICE rawinput[1];

	rawinput[0].usUsagePage = 0x01;
	rawinput[0].usUsage = 0x06;
	rawinput[0].dwFlags = 0;
	rawinput[0].hwndTarget = 0;

	if (RegisterRawInputDevices(rawinput, 1, sizeof(rawinput[0])) == FALSE) return false;

	return true;
}

void EventHandler::update(RAWINPUT* raw)
{
	if (raw->header.dwType == RIM_TYPEKEYBOARD)
	{
		if (raw->data.keyboard.Message == WM_KEYDOWN)
		{
			switch (raw->data.keyboard.VKey)
			{
			case 0x41: //A
				scale_x /= 2;
				std::cout << "Current Scale X: " << scale_x << std::endl;
				break;

			case 0x44: //D
				scale_x *= 2;
				std::cout << "Current Scale X: " << scale_x << std::endl;
				break;

			case 0x53: //S
				scale_y /= 2;
				std::cout << "Current Scale Y: " << scale_y << std::endl;
				break;

			case 0x57: //W
				scale_y *= 2;
				std::cout << "Current Scale Y: " << scale_y << std::endl;
				break;

			default:
				MessageBox(NULL, L"Invalid key was pressed.", NULL, NULL);
			}
		}
	}
}

DirectX::XMMATRIX EventHandler::CheckKeyCode()
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity();

	mat = DirectX::XMMatrixScaling(scale_x, scale_y, scale_z);

	return mat;
}
