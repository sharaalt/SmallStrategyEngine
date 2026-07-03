#include "Definitions.hpp"
#include <SDL3/SDL.h>
#include <vector>
#include <any>

#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

class RenderManager {
	public:
		RenderManager(SDL_Window* window);
		~RenderManager();

		// Rendering Functions
		void AddToBatch(RenderObject& obj);
		void RemoveFromBatch();
		void FlushBatch();
		SDL_Texture ConvertToTexture();
		
		// Misc Functions
		SDL_Renderer* GetRenderer();
	private:
		SDL_Renderer* renderer;
		std::vector<std::any> renderingBatch;
};

#endif // RENDER_MANAGER_HPP