#pragma once
#include <string>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
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

