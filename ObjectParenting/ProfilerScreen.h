#pragma once
#include "AUIScreen.h"
class UIManager;
class ProfilerScreen :public AUIScreen
{
private:
	ProfilerScreen();
	~ProfilerScreen();

	void drawUI() override;
	friend class UIManager;
};

