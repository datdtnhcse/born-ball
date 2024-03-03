#ifndef Bot_hpp
#define Bot_hpp

#include "Game.hpp"
#include "Vector2D.hpp"
#include "Team.hpp"

const int FRAMEBOTRECOUNT = 5;

class Bot {
private:
	Team* controlTeam;
	int needMoveDistance;
	int needRecount;

public:
	Bot(Team* team);
	~Bot();

	void MovePole();
	void UpdateWill(int ballX, int ballY);
};

#endif