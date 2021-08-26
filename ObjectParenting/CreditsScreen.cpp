#include "CreditsScreen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "UIManager.h"
CreditsScreen::CreditsScreen() :AUIScreen("CreditsScreen")
{
	my_image_width = 0;
	my_image_height = 0;
	my_texture = NULL;
	bool ret = GraphicsEngine::get()->LoadTextureFromFile("Logo.jpg", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

CreditsScreen::~CreditsScreen()
{
	AUIScreen::~AUIScreen();
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");
	//ImGui::Text("pointer = %p", my_texture);
	//ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
	ImGui::Image((void*)(intptr_t)my_texture, ImVec2(my_image_width * 0.5f, my_image_height * 0.5f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));
	ImGui::Text("Scene Editor V0.1\n");
	ImGui::Text("By Jacob Lo\n");
	ImGui::Text("Acknowledgements:\n");
	ImGui::Text("PardCode\n");
	ImGui::Text("Sir Neil\n");
	ImGui::End();
}

