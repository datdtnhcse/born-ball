#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

const int BALL_RADIUS = 8;
const int MOVE_STEP = 7;

enum gameState {MENU, END, PLAYWITHBOT, PLAYWITHPERSON};

class Game {
public:
	int state = MENU;
	Game();
	~Game();

	void init(const char* title, int w, int h);
	void start();
	void handleEvents();
	void update();
	void render();
	void clean();
	void checkGameEnd();
	void renderEndScreen();
	void renderMenuScreen();

	bool running();

private:
	bool run;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !Game_hpp
