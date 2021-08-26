#include "UIManager.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "HierarchyScreen.h"
#include "Inspector.h"

UIManager* UIManager::sharedInstance = NULL;\

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

bool UIManager::doesScreenExist(String name)
{
	return this->uTable[name] != nullptr;
}

void UIManager::addUIScreen(AUIScreen* screen)
{
	this->uTable[screen->getName()] = screen;
	this->uList.push_back(screen);
}

void UIManager::deleteUIScreen(AUIScreen* screen)
{
	this->uTable.erase(screen->getName());

	std::vector<AUIScreen*>::iterator it = this->uList.begin();

	while(it != this->uList.end())
	{
		if ((*it)->getName() == screen->name)
		{
			this->uList.erase(it);
			break;
		}
			
		++it;
	}
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uList.size(); i++) {
		this->uList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirectXDevice(), GraphicsEngine::get()->getContext());

	UINames uiNames;
	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uList.push_back(profilerScreen);

	MenuScreen* menuScreen = new MenuScreen();
	this->uTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uList.push_back(menuScreen);

	HierarchyScreen* hierarchy = new HierarchyScreen();
	this->uTable[uiNames.HIERARCHY_SCREEN] = hierarchy;
	this->uList.push_back(hierarchy);

	Inspector* inspector = new Inspector();
	this->uTable[uiNames.INSPECTOR_SCREEN] = inspector;
	this->uList.push_back(inspector);
}

UIManager::~UIManager()
{
}
