#pragma once
#include <string>
typedef std::string String;
class UIManager;
class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	void setActive(bool active);
	
	String Name;
	bool Active;
	friend class UIManager;
};

