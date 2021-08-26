#include "ColorPickerScreen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "UIManager.h"
ColorPickerScreen::ColorPickerScreen() :AUIScreen("ColorPickerScreen")
{
	for (int i = 0; i < 4; i++)
	{
		my_color[i] = 0.0f;
	}
}

ColorPickerScreen::~ColorPickerScreen()
{
	AUIScreen::~AUIScreen();
}

void ColorPickerScreen::drawUI()
{
	ImGui::Begin("Color Picker");

	ImGui::ColorEdit4("Color", my_color);
	ImGui::End();
}
