#include "SceneManager.hpp"

// =======================
// ===== Public API ======
// =======================
/*
	@breif Create's a new entity and push's it to the back of the cache.
*/
entt::entity* SceneManager::CreateEntity(const std::string* objectName, bool isChild, const float* color, const float* position) {
	entt::entity newEntity = registry.create();

	registry.emplace<GameObject>(newEntity, GameObject{ *objectName, isChild });
	registry.emplace<Vector2>(newEntity, position[0], position[1]);
	registry.emplace<Color3>(newEntity, color[0], color[1], color[2], color[3]);

	return &newEntity;
}

/*
	@brief Add's a new component to an already existing entity.
*/
//template<typename T, typename... Args>
//void SceneManager::AddComponent(entt::entity* entity, Args&&... args) {
//	// We assume the prototyped parameter has already been assigned data.
//	registry.emplace<T>(entity, std::forward<Args>(args)...);
//};

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

/*
	@brief Save's the registry to a specified default path.
*/
void SceneManager::SaveScene() {
	auto view = registry.view<GameObject>();

	std::string yaml_content;

	// Main Tree
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	// Scene Data
	ryml::NodeRef sceneData = root["metadata"];
	sceneData |= ryml::MAP;

	sceneData["scenename"] << "null";
	sceneData["savetime"] << GetTimeStamp().c_str();
	sceneData["engineversion"] << "nullvoid";

	// Game Objects
	ryml::NodeRef list = root["scenedata"];
	list |= ryml::SEQ;

	for (const auto entity : view) {
		auto& object = registry.get<GameObject>(entity);

		// Main Tree
		ryml::NodeRef entry = list.append_child();
		entry |= ryml::MAP;

		entry["ObjectName"] << object.ObjectName.data();

		// Create a sub-map for components
		ryml::NodeRef components_node = entry["Components"];
		components_node |= ryml::MAP;

		for (auto [id, storage] : registry.storage()) {
			// Object Components
			if (storage.contains(entity)) {
				void* raw_data = storage.value(entity);

				entt::meta_type type = entt::resolve(storage.info());

				std::cout << "i have no idea if this'll work :D" << '\n';

				if (type) {
					entt::meta_any any = type.from_void(raw_data);

					std::cout << "ja voul?" << '\n';

					for (auto [meta_id, data] : type.data()) {
						entt::meta_any value = data.get(any);

						std::cout << "blegh" << '\n';

						if (auto* val = value.try_cast<float>()) {
							std::cout << "Float: " << *val << '\n';
						} else if (auto* val = value.try_cast<int>()) {
							std::cout << "Int: " << *val << '\n';
						}
					}
				}
			
				//ryml::NodeRef component = components_node[fullTypeName.data()];
				//component |= ryml::MAP; 
			}
		}
	}


	std::filesystem::create_directories("Engine/Saves");

	std::ofstream fout("Engine/Saves/GameObject.yml");

	// Error handling.
	if (!fout.is_open()) {
		std::cout << "Failed to create a new GameObject.yml file." << std::endl;
	}
	
	fout << tree;
	fout.close();
};

// =======================
// ===== Private API =====
// =======================
/*
	For all our private scene management needs!
*/
std::string SceneManager::GetTimeStamp() {
	std::time_t timestamp = std::time(nullptr);

	std::chrono::seconds seconds = std::chrono::seconds(timestamp);
	auto time_of_day = seconds - std::chrono::floor<std::chrono::days>(seconds);
	std::chrono::hh_mm_ss c{ time_of_day };

	return std::format("{:02}:{:02}:{:02}",
		c.hours().count(),
		c.minutes().count(),
		c.seconds().count()
	);
}