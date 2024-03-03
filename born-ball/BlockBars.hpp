#ifndef BlockBars_hpp
#define BlockBars_hpp

#include "Game.hpp"

class BlockBars {
private:
	SDL_Texture* blockBarsTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;

public:
	BlockBars(SDL_Renderer* rend);
	~BlockBars();

	void Render();
};

#endif
