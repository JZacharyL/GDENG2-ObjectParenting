#include "AUIScreen.h"

AUIScreen::AUIScreen(std::string name)
{
	this->Name = name;
	this->Active = true;
}

AUIScreen::~AUIScreen()
{
	
}

std::string AUIScreen::getName()
{
    return this->Name;
}

void AUIScreen::setActive(bool active)
{
	this->Active = active;
}
