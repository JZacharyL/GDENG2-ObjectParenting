#pragma once
#include <string>
#include <Windows.h>
#include "KeyboardClass.h"
#include "EngineTime.h"
#include  "imgui\imgui.h"
#include  "imgui\imgui_impl_win32.h"

#include  "imgui\imgui_impl_dx11.h"
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
	HWND getHWND();
	 char getKey();

	

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

