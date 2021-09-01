#include "Inspector.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
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
		if (ImGui::InputFloat3("Position", this->positionDisplay, 4));

		if (ImGui::IsItemDeactivatedAfterEdit()) {
			this->onTranslateUpdate();
		}

		if (ImGui::InputFloat3("Rotation", this->rotationDisplay, 4));

		if (ImGui::IsItemDeactivatedAfterEdit()) {
			this->onRotateUpdate();
		}

		if (ImGui::InputFloat3("Scale", this->scaleDisplay, 4));

		if (ImGui::IsItemDeactivatedAfterEdit()) {
			this->onScaleUpdate();
		}
		
		//Parent child UI
		string parentTitle;
		if (this->selectedObject->isChild()) {
			//Header
			parentTitle = ("Object parent: %s", this->selectedObject->getParent()->getName());
		}

		else {
			parentTitle = "Object parent: None";
		}

		//header
		ImGui::Text(parentTitle.c_str());
		static char str0[128];
		ImGui::InputText("Set New Parent", str0, IM_ARRAYSIZE(str0));
		string textVal = str0;

		if (ImGui::IsItemEdited()) {
			//if the text field request an actual object
			if (GameObjectManager::getInstance()->findObjectByName(textVal) != NULL) {
				//Set object as parent
				cout << textVal << endl;

				AGameObject* newParent = GameObjectManager::getInstance()->findObjectByName(textVal);
				newParent->addChild(selectedObject);
			}

			else{
				selectedObject->unsetParent();
			}
		}

		//cout << textVal << endl;
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
	this->rotationDisplay[0] = rot.getX() / 0.0174533;
	this->rotationDisplay[1] = rot.getY() / 0.0174533;
	this->rotationDisplay[2] = rot.getZ() / 0.0174533;

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
		this->selectedObject->setScale(Vector3D(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]));

		//* 0.0174533

		float rotX = this->rotationDisplay[0] * 0.0174533;
		float rotY = this->rotationDisplay[1] * 0.0174533;
		float rotZ = this->rotationDisplay[2] * 0.0174533;

		this->selectedObject->setRotation(Vector3D(rotX, rotY, rotZ));

		this->selectedObject->setPosition(Vector3D(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]));
	}
}

void Inspector::onTranslateUpdate()
{
	if (this->selectedObject != NULL) {
		this->selectedObject->setPosition(Vector3D(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]));
	}
}

void Inspector::onRotateUpdate()
{
	if (this->selectedObject != NULL) {
		//* 0.0174533

		float rotX = this->rotationDisplay[0] * 0.0174533;
		float rotY = this->rotationDisplay[1] * 0.0174533;
		float rotZ = this->rotationDisplay[2] * 0.0174533;

		this->selectedObject->setRotation(Vector3D(rotX, rotY, rotZ));
	}
}

void Inspector::onScaleUpdate()
{
	if (this->selectedObject != NULL) {
		this->selectedObject->setScale(Vector3D(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]));
	}
}
