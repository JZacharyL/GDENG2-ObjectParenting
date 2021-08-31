#include "MenuScreen.h"
#include "UIManager.h"
#include "CreditsScreen.h"
#include "GameObjectManager.h"
#include "VertexShader.h"
#include "ShaderLibrary.h"
MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{
}

MenuScreen::~MenuScreen()
{
	AUIScreen::~AUIScreen();
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) 
			{
				if(!UIManager::getInstance()->doesScreenExist("CreditsScreen"))
					UIManager::getInstance()->addUIScreen(new CreditsScreen());
			}
			ImGui::EndMenu();
		}
		else if (ImGui::BeginMenu("Tools"))
		{
            static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

            static bool alpha_preview = true;
            static bool alpha_half_preview = false;
            static bool drag_and_drop = true;
            static bool options_menu = true;
            static bool hdr = false;
            ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

            // Generate a default palette. The palette will persist and can be edited.
            static bool saved_palette_init = true;
            static ImVec4 saved_palette[32] = {};
            if (saved_palette_init)
            {
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                {
                    ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
                        saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                    saved_palette[n].w = 1.0f; // Alpha
                }
                saved_palette_init = false;
            }

            static ImVec4 backup_color;
            if (ImGui::Button("Palette"))
            {
                ImGui::OpenPopup("mypicker");
                backup_color = color;
            }
            if (ImGui::BeginPopup("mypicker"))
            {	
                ImGui::Text("Color Palette");
                ImGui::Separator();
                ImGui::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
                ImGui::SameLine();

                ImGui::BeginGroup(); // Lock X position
                ImGui::Text("Current");
                ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
                ImGui::Text("Previous");
                if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
                    color = backup_color;
                ImGui::Separator();
                ImGui::Text("Palette");
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                {
                    ImGui::PushID(n);
                    if ((n % 8) != 0)
                        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

                    ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
                    if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
                        color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

                    // Allow user to drop colors into each palette entry. Note that ColorButton() is already a
                    // drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                        ImGui::EndDragDropTarget();
                    }

                    ImGui::PopID();
                }
                ImGui::EndGroup();
                ImGui::EndPopup();
            }
			ImGui::EndMenu();
		}
        else if (ImGui::BeginMenu("Primitives")) {
            if (ImGui::MenuItem("Cube"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::CUBE);
            }

            if (ImGui::MenuItem("Plane"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::PLANE);


            }
        	
            if (ImGui::MenuItem("TexturedCube"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::TEXTURED_CUBE);


            }

            if (ImGui::MenuItem("Teapot"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::TEAPOT);


            }
            if (ImGui::MenuItem("Bunny"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::BUNNY);


            }
        	
            if (ImGui::MenuItem("Armadillo"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::ARMADILLO);


            }
            if (ImGui::MenuItem("Physics Cube"))
            {
                //Call to game object manager
                GameObjectManager::getInstance()->createObject(PrimitiveType::PHYSICS_CUBE);


            }

        	if(ImGui::MenuItem("Physics Plane"))
        	{
                GameObjectManager::getInstance()->createObject(PrimitiveType::PHYSICS_PLANE);

        	}
            ImGui::EndMenu();
        }
		ImGui::EndMainMenuBar();
	}
}
