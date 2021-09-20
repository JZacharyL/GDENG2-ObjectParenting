#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"

class UINames
{
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const String ACTION_SCREEN = "ACTION_SCREEN";
};

