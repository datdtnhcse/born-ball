#include "Yard.hpp"
#include "TextureManager.hpp"

Yard::Yard(SDL_Renderer* rend) {
	yardTexture = TextureManager::LoadImage("Images/yard.png", rend);
	
	renderer = rend;

	dstRect.x = 100;
	dstRect.y = 100;
	dstRect.w = 800;
	dstRect.h = 400;
}

Yard::~Yard() {}

void Yard::Render() {
	SDL_RenderCopy(renderer, yardTexture, NULL, &dstRect);
}
