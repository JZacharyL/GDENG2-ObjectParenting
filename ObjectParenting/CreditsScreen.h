#pragma once
#include "AUIScreen.h"
#include "GraphicsEngine.h"

class UIManager;
class MenuScreen;

class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen();
	~CreditsScreen();

	virtual void drawUI() override;

	friend class UIManager;
	friend class MenuScreen;

	ID3D11ShaderResourceView* imageTexture = nullptr;
	int width = 0;
	int height = 0;
};

