#pragma once
#include "AUIScreen.h"


class UIManager;
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;

	friend class UIManager;
};

