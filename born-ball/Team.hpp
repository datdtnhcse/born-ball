#ifndef Team_hpp
#define Team_hpp

#include "Game.hpp"
#include "PlayerPole.hpp"

class Team {
private:
	PlayerPole** playerPoles = new PlayerPole*[4];
	bool onLeftSide;
	int score;

public:
	Team(SDL_Renderer* rend, bool leftSide);
	~Team();

	void Move(int distance);
	void AddScore();
	int GetScore();
	bool OnLeftSide();
	PlayerPole** GetPlayerPoles();

	void Render();
};

#endif

