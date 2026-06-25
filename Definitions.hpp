#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Base Components
struct GameObject {
	std::string ObjectName;
	float Color[4];
	float Position[2];

	std::vector<GameObject*> children;

	void AddChild(GameObject* child) {
		if (child) {
			children.emplace_back(child);
		}
	};

	std::vector<GameObject*> GetChildren() {
		return children;
	}
};

struct Parent {
	entt::entity handle;
};

// Components
struct Color3 {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
};

struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;

	std::vector<float> returnVector() {
		return { x, y };
	}
};


#endif // !DEFINITIONS_HPP