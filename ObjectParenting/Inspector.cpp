#include "Inspector.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"

Inspector::Inspector() : AUIScreen("Inspector")
{
}

Inspector::~Inspector()
{
}

void Inspector::drawUI()
{
	ImGui::Begin("Inspector Window");
	//ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 20));
	//ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->selectedObject = GameObjectManager::getInstance()->getSelectedObject();
	if (this->selectedObject != NULL) {
		String name = this->selectedObject->getName();
		ImGui::Text("Selected Object: %s", name.c_str());

		this->updateTransformDisplays();
		bool enabled = this->selectedObject->isEnabled();
		if (ImGui::Checkbox("Enabled", &enabled)) { this->selectedObject->setEnabled(enabled); }
		if (ImGui::InputFloat3("Position", this->positionDisplay, 4)) { this->onTransformUpdate(); }
		if (ImGui::InputFloat3("Rotation", this->rotationDisplay, 4)) { this->onTransformUpdate(); }
		if (ImGui::InputFloat3("Scale", this->scaleDisplay, 4)) { this->onTransformUpdate(); }
		
		//Parent child UI
		static char str0[128];
		if (this->selectedObject->isChild()) {
			string parentName = this->selectedObject->getParent()->getName();
			static char str0[128] = "%s\n", parentName;
		}

		else {
			static char str0[128] = "None";
		}
		 
		ImGui::InputText("Parent Object", str0, IM_ARRAYSIZE(str0));
		string textVal = str0;

		cout << textVal << endl;
	}
	else {
		ImGui::Text("No object selected. Select an object first.");
	}
	ImGui::End();
}

void Inspector::updateTransformDisplays()
{
	Vector3D pos = this->selectedObject->getLocalPosition();
	this->positionDisplay[0] = pos.getX();
	this->positionDisplay[1] = pos.getY();
	this->positionDisplay[2] = pos.getZ();

	Vector3D rot = this->selectedObject->getLocalRotation();
	this->rotationDisplay[0] = rot.getX();
	this->rotationDisplay[1] = rot.getY();
	this->rotationDisplay[2] = rot.getZ();

	Vector3D scale = this->selectedObject->getLocalScale();
	this->scaleDisplay[0] = scale.getX();
	this->scaleDisplay[1] = scale.getY();
	this->scaleDisplay[2] = scale.getZ();

	//Text input field thingy
	//ImGui::InputText("##text1", buf1, bufSize);
}

void Inspector::onTransformUpdate()
{
	if (this->selectedObject != NULL) {
		this->selectedObject->setPosition(Vector3D(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]));
		this->selectedObject->setRotation(Vector3D(this->rotationDisplay[0], this->rotationDisplay[1], this->rotationDisplay[2]));
		this->selectedObject->setScale(Vector3D(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]));
	}
}