#include "Hierarchy.hpp"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <ImGui/imgui_impl_sdlrenderer3.h>

#include <iostream>
#include <SDL3/sdl.h>


// Literally the main function for the program.
int main() {
	// Initalizes everything we need.
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initalize certain streams: %s\n", SDL_GetError());
		return 1;
	};

	// Create's our window cunningly named "TheWindow"
	SDL_Window* window = SDL_CreateWindow("TheWindow", 500, 500, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL); // Why was this the issue? We'll never know.

	// GUI Objects
	HierarchyGUI hierarchy;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	// Variables
	bool isRunning = true;

	// Main game loop.
	while (isRunning) {
		SDL_Event event;
			
		// Event Polling
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);

			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}
		
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		// Display demo
		ImGui::ShowDemoWindow();

		// Scene Viewport
		ImGui::Begin("Scene View");
		ImGui::DockSpaceOverViewport(1, ImGui::GetMainViewport());
		ImGui::End();

		hierarchy.DisplayGUI();

		// Rendering Pipeline
		ImGui::Render();
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup (don't leak more memory)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}