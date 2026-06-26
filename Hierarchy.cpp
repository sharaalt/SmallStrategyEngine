#include "Hierarchy.hpp"

/*
	@class Hierarchy
	@version 1.0.0

	@todo Add hierarchy saving/loading
	@todo Integrate with SceneManager.cpp

	The Hierarchy GUI is used to display Hierarchy of object's in a human understandable GUI. Furthermore,
	it also handle's the creation of new GameObjects (with assistance from SceneManager.cpp) and presents
	them in a human understandable GUI.
	
	@note I call TreePop/PopId "popping the lolipop" not really any reason behind that I just like to call it that :-)
*/

/*
	@brief Initalize's the Hierarchy GUI.
*/
HierarchyGUI::HierarchyGUI(SceneManager& scene) : scene(&scene) { /* Long story short this is a waste of space */ }

// =======================
// ===== Public API ======
// =======================
/*
	@brief Display's the GUI for Hierarchy.
*/
void HierarchyGUI::DisplayGUI() {
	ImGui::Begin("Hierarchy");

	if (ImGui::Button("Create New Object")) {
		ImGui::OpenPopup("New Object");
	}

	this->CreateObjectModal();

	entt::registry* registry = scene->GetRegistry();

	for (auto entity : registry->view<GameObject>()) {
		// Base Properties
		auto& Object = registry->get<GameObject>(entity);

		if (Object.isChild) {
			continue;
		}

		auto& Color = registry->get<Color3>(entity);
		auto& Position = registry->get<Vector2>(entity);

		auto id = entt::to_integral(entity);

		ImGui::PushID(id);

		std::string nodeLabel = std::string(Object.ObjectName) + "###Node_";

		static bool isDisabled = false;
		static bool openDeletePopup = false;
		static bool doNotAskAgain = false;
		bool opened = ImGui::TreeNodeEx(nodeLabel.c_str());

		std::string contextId = std::string(Object.ObjectName) + "'s ContextMenu ";

		if (ImGui::BeginPopupContextItem("ObjectContextMenu")) {
			ImGui::SeparatorText(contextId.c_str());
			if (ImGui::MenuItem("Disable Object", NULL, &isDisabled)) {}
			if (ImGui::MenuItem("Destroy Object")) {
				openDeletePopup = true;
			};

			ImGui::EndPopup();
		}

		// Opens the deletion popup.
		if (openDeletePopup) {
			ImGui::OpenPopup("Delete?");
		}

		// Deletion popup
		if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Separator();

			ImGui::Text("Are you sure you want to delete this object?");
			ImGui::Checkbox("Dont ask me again", &doNotAskAgain);

			// Fix this!
			//if (doNotAskAgain) {
			//	ImGui::CloseCurrentPopup();
			//}

			// Confirms the deletions and properly delete's the object.
			if (ImGui::Button("Confirm", ImVec2(140, 0))) {
				openDeletePopup = false;
				//GameObjects.erase(GameObjects.begin() + i);
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			// Cancels the deletion and exits the UI.
			if (ImGui::Button("Cancel", ImVec2(140, 0))) {

			}

			ImGui::EndPopup();
		}

		// Popup for object data.
		if (opened) {
			// Basic data for GameObjects
			ImGui::Text("General Data:");
			ImGui::InputText("Object Name", &Object.ObjectName);
			ImGui::SameLine(); HelpMarker("Set's the Object name.");
			ImGui::ColorEdit4("Color:", Color.rgba);
			ImGui::SameLine(); HelpMarker("Set's the Object colour.");
			ImGui::InputFloat2("Position:", Position.position);
			ImGui::SameLine(); HelpMarker("Set's the Object position.");

			// Children
			ImGui::SeparatorText("Children");

			if (ImGui::Button("Add Component")) {
				ImGui::OpenPopup("New Object");
			}

			// Opens the modal for creating children.
			this->CreateObjectModal(&entity);

			if (auto* childNodes = registry->try_get<Parent>(entity)) {
				// Renders children nodes.
				for (auto node : childNodes->children) {
					this->RenderNode(node);
				}
			}
 
			// Pop's the lolipop.
			ImGui::TreePop();
		}

		ImGui::PopID();
	}

	ImGui::End();
}


// =======================
// ===== Private API =====
// =======================
/*
	@brief Helper function to create a popup modal for new objects.
*/
void HierarchyGUI::CreateObjectModal() {
	// The basis for object creation.
	if (ImGui::BeginPopupModal("New Object", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		static char buff[32];
		static float color[4];
		static float position[2];

		ImGui::Text("Create New Object");

		// Allows for data input.
		ImGui::SeparatorText("Input Data:");
		ImGui::InputText("Object Name", buff, IM_ARRAYSIZE(buff));
		ImGui::SameLine(); HelpMarker("Set's the Game Object's name.");
		ImGui::ColorEdit4("Color", color);
		ImGui::SameLine(); HelpMarker("Set's the Game Object's color.");
		ImGui::InputFloat2("Position", position);
		ImGui::SameLine(); HelpMarker("Set's the Game Object's world position.");

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Create")) {
			if (buff[0] != '\0') {
				std::string objName(buff);

				scene->CreateEntity(&objName, false, color, position);

				//newObject->ObjectName = buff;
				//
				//for (int i = 0; i < 4; i++) {
				//	newObject->Color[i] = color[i];
				//}

				//for (int i = 0; i < 2; i++) {
				//	newObject->Position[i] = position[i];
				//}


				//GameObjects.emplace_back(newObject);

				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::EndPopup();
	}
}

/*
	@brief Helper function to create a popup modal for children nodes.
*/
void HierarchyGUI::CreateObjectModal(entt::entity* parentObj) {
	// The basis for object creation.
	if (ImGui::BeginPopupModal("New Object", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		static std::string buff = "";
		static float color[4];
		static float position[2];

		ImGui::Text("Create New Object");

		// Allows for data input.
		ImGui::SeparatorText("Input Data:");
		ImGui::InputText("Object Name", &buff);
		ImGui::SameLine(); HelpMarker("Set's the Game Object's name.");
		ImGui::ColorEdit4("Color", color);
		ImGui::SameLine(); HelpMarker("Set's the Game Object's color.");
		ImGui::InputFloat2("Position", position);
		ImGui::SameLine(); HelpMarker("Set's the Game Object's world position.");

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Create")) {
			if (buff[0] != '\0') {
				entt::registry* view = scene->GetRegistry();
				entt::entity* child = scene->CreateEntity(&buff, true, color, position);
				//entt::entity objEntity = scene->GetEntity(parentObj->ObjectName);
				
				if (!view->all_of<Parent>(*parentObj)) {
					scene->AddComponent<Parent>(*parentObj, *parentObj, std::vector<entt::entity>());
				}

				auto& parentComp = view->get<Parent>(*parentObj);
				parentComp.children.push_back(*child);

				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::EndPopup();
	}
}

/*
	@brief Add's a tool tip to the end of line's.
*/
void HierarchyGUI::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

/*
	@brief Display's children using a Depth First Search algoritihm.
*/
void HierarchyGUI::RenderNode(entt::entity& node) {
	entt::registry* view = scene->GetRegistry();

	// Base Properties
	auto& gameObj = view->get<GameObject>(node);
	auto& Color = view->get<Color3>(node);
	auto& Position = view->get<Vector2>(node);

	auto id = entt::to_integral(node);

	// What does this do? Something.
	bool opened = ImGui::TreeNode((void*)&node, "%s", gameObj.ObjectName.c_str());

	if (opened) {
		ImGui::PushID(id);

		// General Data
		ImGui::Text("General Data:");
		ImGui::InputText("Object Name", &gameObj.ObjectName);
		ImGui::SameLine(); HelpMarker("Set's the Object name.");
		ImGui::ColorEdit4("Color:", Color.rgba);
		ImGui::SameLine(); HelpMarker("Set's the Object colour.");
		ImGui::InputFloat2("Position:", Position.position);
		ImGui::SameLine(); HelpMarker("Set's the Object position.");

		// Children
		ImGui::SeparatorText("Children");

		// Allow for additional components/objects
		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("New Object");
		}

		this->CreateObjectModal(&node);

		// If there's any children we also render them DFS algorithim for the win!
		if (auto* childNodes = view->try_get<Parent>(node)) {
			for (auto nextChild : childNodes->children) {
				this->RenderNode(nextChild);
			}
		}

		ImGui::PopID();

		// Pop the lolipop!
		ImGui::TreePop();
	}
};