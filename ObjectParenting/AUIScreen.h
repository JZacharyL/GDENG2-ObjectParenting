#pragma once
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "GraphicsEngine.h"

typedef std::string String;
class UIManager;

class AUIScreen
{
protected:
	AUIScreen(String name);
	~AUIScreen();

	String getName();
	virtual void drawUI() = 0;

	String name;

	friend class UIManager;
};

