#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadImage(const char* fileName, SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return text;
}

SDL_Texture* TextureManager::LoadText(const char* text, SDL_Renderer* renderer, SDL_Color color, TTF_Font* font) {
	SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return textture;
}