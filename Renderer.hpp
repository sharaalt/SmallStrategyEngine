#include "Definitions.hpp"
#include <iostream>
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <vector>

#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
	public:
		Renderer(SDL_Window* window);

		// Renderer Functions
		void addRect();

		// Pipeline Functions
		void addToBatch();
		void releaseBatch();
	private:
		SDL_Renderer* renderer;
		std::vector<SDL_FRect*> renderBatch;
};

#endif // !RENDERER_HPP
