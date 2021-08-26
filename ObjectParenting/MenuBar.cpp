#include "MenuBar.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "UIManager.h"

MenuBar::MenuBar() :AUIScreen("MenuBar")
{
	
}

MenuBar::~MenuBar()
{
	AUIScreen::~AUIScreen();
}

void MenuBar::drawUI()
{
  
	ImGui::Begin("Toolbar", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits"))
            {
                creditstoggle = !creditstoggle;
	            /* Do stuff */
                UIManager::getInstance()->setEnabled("CREDITS_SCREEN", creditstoggle);
            }

            if (ImGui::MenuItem("ColorUIPicker"))
            {
                // Edit a color (stored as ~4 floats)
                ColorUIToggle = !ColorUIToggle;
                UIManager::getInstance()->setEnabled("COLORUI_SCREEN", ColorUIToggle);
            }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
            ImGui::EndMenu();
        }
    	
        ImGui::EndMenuBar();
    }
    ImGui::End();
}
