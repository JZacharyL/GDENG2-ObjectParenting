#include "ProfilerScreen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "UIManager.h"
ProfilerScreen::ProfilerScreen():AUIScreen("ProfilerScreen")
{
}

ProfilerScreen::~ProfilerScreen()
{
	AUIScreen::~AUIScreen();
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("GDENG-2 Engine Profiler");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
	ImGui::End();
}