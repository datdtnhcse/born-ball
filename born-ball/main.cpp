#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	
	game->init("born-ball", 1000, 600);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();

		if (game->state == PLAYWITHBOT || game->state == PLAYWITHPERSON) {
			game->checkGameEnd();
			game->update();
		}
		if (game->state == MENU) {
			game->renderMenuScreen();
		}
		else {
			game->render();
		}

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}