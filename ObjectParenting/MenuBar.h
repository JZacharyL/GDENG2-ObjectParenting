#pragma once
#include "AUIScreen.h"
class UIManager;
class MenuBar : public AUIScreen
{
private:
	MenuBar();
	~MenuBar();

	void drawUI() override;
	friend class UIManager;

	float my_color[4];
	bool my_tool_active = true;
	bool creditstoggle = false;
	bool ColorUIToggle = false;
};

