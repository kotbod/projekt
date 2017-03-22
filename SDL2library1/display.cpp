#include <iostream>

#include <string>
#include <SDL.h>
#include "display.h"

Display::Display(int width, int height) {
	window = SDL_CreateWindow("Program graficzny", 200, 200, width, height, SDL_WINDOW_RESIZABLE);
	window_surface = SDL_GetWindowSurface(window);
	//window_surface = SDL_CreateRGBSurface(0, width, height, 24, 0, 0, 0, 0);
	renderer = SDL_CreateSoftwareRenderer(window_surface);
	//SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
}

Display::~Display() {
	for (SDL_Texture* texture : texture_pool) {
		SDL_DestroyTexture(texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

}

SDL_Renderer* Display::get_renderer() {
	return renderer;
}

SDL_Window* Display::get_window() {
	return window;
}

SDL_Texture* Display::load_texture(std::string path) {
	SDL_Texture* texture;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == nullptr) {
		std::cout << "Nie mozna otworzyc " << path << std::endl;
		return nullptr;
	}	
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	texture_pool.push_back(texture);
	return texture;
}

void Display::update() {
	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
}

