#ifndef PlayerPole_hpp
#define PlayerPole_hpp

#include "Player.hpp"

enum posOnYard {
	POS0ONYARD = 112,
	POS1ONYARD = 221,
	POS2ONYARD = 330,
	POS3ONYARD = 439,
	POS4ONYARD = 548,
	POS5ONYARD = 657,
	POS6ONYARD = 766,
	POS7ONYARD = 875,
};

class PlayerPole {
private:
	SDL_Texture *playerPoleTexture;
	SDL_Rect dstRect;
	SDL_Renderer *renderer;
	bool inRedTeam;
	int playersNum;
	Player** players;
	int maxY, minY;

public:
	PlayerPole(SDL_Renderer* rend, bool isRedTeam, int posYard, int numOfPlayers);
	~PlayerPole();

	Player** GetPlayers();
	int GetPlayersNum();
	void Move(int distance);

	void Render();
};

#endif
