#pragma once
#include "AUIScreen.h"
class ColorPickerScreen : public AUIScreen
{
private:
	ColorPickerScreen();
	~ColorPickerScreen();


	float my_color[4];
	void drawUI() override;
	friend class UIManager;
};

