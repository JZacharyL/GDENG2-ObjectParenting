#pragma once
#include <unordered_map>

#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include  "Window.h"
#include "AUIScreen.h"
#include "ProfilerScreen.h"
#include  "MenuBar.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "GraphicsEngine.h"
class UINames
{
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLORUI_SCREEN = "COLORUI_SCREEN";
};

class UIManager
{
public:
	typedef  std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	void setEnabled(String uiName, bool flag);
	AUIScreen* findUIByName(String uiName);
	static const int Window_Width = 1440;
	static const int Window_Height = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
	
};

