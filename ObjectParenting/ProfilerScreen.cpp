#include "ProfilerScreen.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

ProfilerScreen::ProfilerScreen() : AUIScreen("ProfilerScreen")
{
}

ProfilerScreen::~ProfilerScreen()
{
	AUIScreen::~AUIScreen();
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Profiler");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	ImGui::End();
}
