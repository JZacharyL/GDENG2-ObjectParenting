#pragma once
//#define NOMINMAX
#include <Windows.h>
#include <DirectXMath.h>
#include "EngineTime.h"
#include "UIManager.h"

class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);
	void input(RAWINPUT* raw);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	~Window();
	
protected:
	HWND m_hwnd;
	bool m_is_run;

};

