#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {
public:
	static SDL_Texture* LoadImage(const char* fileName, SDL_Renderer* renderer);
	static SDL_Texture* LoadText(const char* text, SDL_Renderer* renderer, SDL_Color color, TTF_Font* font);
};

#endif
