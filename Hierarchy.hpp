#include "Definitions.hpp"
#include "SceneManager.hpp"
#include <iostream>
#include <ImGui/imgui.h>
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <ImGui/misc/cpp/imgui_stdlib.h>

#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

class HierarchyGUI {
	public:
		HierarchyGUI();
		void DisplayGUI();
	private:	
		void CreateObjectModal();
		void CreateObjectModal(GameObject* parentObj);
		void HelpMarker(const char* desc);
		void RenderNode(GameObject& node);

		SceneManager* scene;
		//std::vector<GameObject*> GameObjects;
};

#endif //!HIERARCHY_HPP