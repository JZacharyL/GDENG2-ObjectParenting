#pragma once
#include "AUIScreen.h"
#include "imfilebrowser.h"

class UIManager;
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;

	friend class UIManager;
	bool isOpen = false;

	bool openSceneSelected = false;

	ImGui::FileBrowser* saveSceneDialog;
	ImGui::FileBrowser* openSceneDialog;
};

