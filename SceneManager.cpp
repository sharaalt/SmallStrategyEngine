#include "SceneManager.hpp"

// =======================
// ===== Public API ======
// =======================
/*
	@breif Create's a new entity and push's it to the back of the cache.
*/
void SceneManager::CreateEntity(const std::string* objectName, const float* color, const float* position) {
	entt::entity newEntity = registry.create();

	registry.emplace<Vector2>(newEntity, position[0], position[1]);
	registry.emplace<Color3>(newEntity, color[0], color[1], color[2], color[3]);
}

/*
	@brief Add's a new component to an already existing entity.
*/
template<typename T>
void SceneManager::AddComponent(entt::entity* entity, const T& component) {
	// We assume the prototyped parameter has already been assigned data.
	registry.emplace<T>(entity);
};

/*
	@brief Remove's a component from an already existing entity.
*/
template<typename T>
void SceneManager::RemoveComponent(entt::entity* entity, const T& component) {
	if (registry.any_of<component>(entity)) {
		registry.erase<component>(entity);
	} else {
		std::cout << "[SceneManager] - Could not find component in entity.";
	}
}

/*
	@brief Retrive's a entity from the registry based on name.
*/
entt::entity SceneManager::GetEntity(std::string& EntityName) {
	// Retrive all entitys with the tag gameobject (literally all of them).
	auto view = registry.view<GameObject>();

	// Loops through haystack (registry) to find the needle (entity).
	for (auto entity : view) {
		const auto& entityName = view.get<GameObject>(entity);

		// If we have a match return the entity as a pointer to reduce copies and allow for accurate data/changes.
		if (entityName.ObjectName == EntityName) {
			return entity;
		}
	}

	// There's WAY better way's to concat strings.
	std::cout << "[SceneManager] - Could not find entity with name " << EntityName << ".";

	return entt::null;
}

/*
	@brief Returns the registry cache.
	@return entt::registry*
	
*/
entt::registry* SceneManager::GetRegistry() {
	return &registry;
}

// =======================
// ===== Private API =====
// =======================
/*
	For all our private scene management needs!
*/