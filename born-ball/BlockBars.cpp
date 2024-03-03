#include "BlockBars.hpp"
#include "TextureManager.hpp"

BlockBars::BlockBars(SDL_Renderer* rend) {
	renderer = rend;
	
	dstRect.x = 73;
	dstRect.y = 73;
	dstRect.w = 854;
	dstRect.h = 454;
	
	blockBarsTexture = TextureManager::LoadImage("Images/blockBars.png", rend);
}

BlockBars::~BlockBars() {}

void BlockBars::Render() {
	SDL_RenderCopy(renderer, blockBarsTexture, NULL, &dstRect);
}