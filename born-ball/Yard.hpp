#ifndef Yard_hpp
#define Yard_hpp

#include "Game.hpp"

class Yard {
private:
	SDL_Texture* yardTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;

public:
	Yard(SDL_Renderer* rend);
	~Yard();

	void Render();
};

#endif
