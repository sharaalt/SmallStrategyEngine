#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Definitions.hpp"
#include <iostream>
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>

class SceneManager {
	public:
		// Entity Functions
		void CreateEntity(const std::string* objectName, const float* color, const float* position);

		template<typename T>
		void AddComponent(entt::entity* entity, const T& parameter);
		template<typename T>
		void RemoveComponent(entt::entity* entity, const T& component);
		entt::entity GetEntity(std::string& EntityName);

		// Registry Functions
		entt::registry* GetRegistry();
	private:
		entt::registry registry;
};

#endif // !SCENEMANAGER_HPP
