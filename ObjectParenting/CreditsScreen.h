#pragma once
#include "AppWindow.h"
#include "AUIScreen.h"
class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen();
	~CreditsScreen();

	
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;
	void drawUI() override;
	friend class UIManager;
};

