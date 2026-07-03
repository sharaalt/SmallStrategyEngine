#include "RenderManager.hpp"

/*
	@class RenderManager
	@version 1.0.0

	The Render Manager manage's the lifecycle and rendering of object's onto the editor screen. Furthermore, it also convert's it into a 
	displayable texture which can be displayed onto the viewport.
*/

/*
	@brief Initalizes the RenderManager.
*/
RenderManager::RenderManager(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, NULL);
}

/*
	@brief Deconstructs the RenderManager.
*/
RenderManager::~RenderManager() {

}

// =======================
// ===== Public API ======
// =======================
/*
	@brief Add's more renderable item's to the batch.
*/
void RenderManager::AddToBatch(RenderObject& object) {
	std::cout << object.object.w << '\n';
}

/*
	@brief Remove's data from the batch.
*/
void RenderManager::RemoveFromBatch() {

}

/*
	@brief Flush's the batch to the render pipeline.
*/
void RenderManager::FlushBatch() {

}

/*
	@brief Convert's the rendered item's into a texture.
*/
//SDL_Texture RenderManager::ConvertToTexture() {
//
//}

// =======================
// ===== Private API =====
// =======================
/*
	For all of our privatization needs :-)
*/