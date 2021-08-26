#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"
#include "UINames.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	bool doesScreenExist(String name);
	void addUIScreen(AUIScreen* screen);
	void deleteUIScreen(AUIScreen* screen);
	void drawAllUI();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uList;
	UITable uTable;
};

