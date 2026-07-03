#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

// Renderer Definitions
struct RenderObject {
	SDL_Rect object;

	SDL_Rect* returnObject() {
		return &object;
	};

	RenderObject(int x, int y, int w, int h) {
		object = SDL_Rect{ x, y, w, h };
	}
};

// Base Components
struct GameObject {
	std::string ObjectName;
	bool isChild = false;

	GameObject(const std::string& name, const bool child) {
		ObjectName = name;
		isChild = child;
	}
};

struct Parent {
	entt::entity parentObj;
	std::vector<entt::entity> children;
};

// Components
struct Color3 {
	float rgba[4];
};

struct Vector2 {
	float position[2];

	//std::vector<float> returnVector() {
	//	return { x, y };
	//}
};


#endif // !DEFINITIONS_HPP