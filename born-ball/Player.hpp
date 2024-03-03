#ifndef Player_hpp
#define Player_hpp

#include "Game.hpp"

enum posOnPole {
	POS0ONPOLE = 125,
	POS1ONPOLE = 205,
	POS2ONPOLE = 285,
	POS3ONPOLE = 360,
	POS4ONPOLE = 440,
};

enum playerAction {
	NORMAL, KICKRIGHT, KICKLEFT, RIGHT2LEFT, LEFT2RIGHT
};

class Player {
private:
	SDL_Texture* playerTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;
	int posPoleOnYard;
	bool inRedTeam;
	int action;
	int actionSteps;

public:
	Player(SDL_Renderer* rend, int posPole, int posYard, bool isRedTeam);
	~Player();

	void Move(int distance);
	void KickRight();
	void KickLeft();
	void Normal();
	void SetAction(int act);
	SDL_Rect GetRect();
	int CountSqrDistance(int ballX, int ballY);

	void Render();
};

#endif
