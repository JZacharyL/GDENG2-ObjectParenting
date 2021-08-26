#include "UIManager.h"
UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size();i++)
	{
		if (uiList[i]->Active == true) {
			this->uiList[i]->drawUI();
		}
	}
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::setEnabled(String uiName, bool flag)
{
	if(this->uiTable[uiName] != nullptr)
	{
		this->uiTable[uiName]->setActive(flag);
	}
}

AUIScreen* UIManager::findUIByName(String uiName)
{
	if(this->uiTable[uiName] != nullptr)
	{
		return this->uiTable[uiName];
	}

	else
	{
		return nullptr;
	}
}

UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getDeviceContext());

	UINames uiNames;
	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	MenuBar* menuScreen = new MenuBar();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->uiTable[uiNames.COLORUI_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);
}

UIManager::~UIManager()
{
}
