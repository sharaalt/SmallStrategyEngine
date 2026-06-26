#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Definitions.hpp"
#include <iostream>
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>

class SceneManager {
	public:
		// Entity Functions
		entt::entity* CreateEntity(const std::string* objectName, bool isChild, const float* color, const float* position);

		template<typename T, typename... Args>
		void AddComponent(entt::entity entity, Args&&... args) {
			// We assume the prototyped parameter has already been assigned data.
			registry.emplace<T>(entity, std::forward<Args>(args)...);
		};

		template<typename T>
		void RemoveComponent(entt::entity* entity, const T& component);
		entt::entity GetEntity(std::string& EntityName);

		// Registry Functions
		entt::registry* GetRegistry();
	private:
		entt::registry registry;
};

#endif // !SCENEMANAGER_HPP
