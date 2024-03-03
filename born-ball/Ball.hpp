#ifndef Ball_hpp
#define Ball_hpp

#include "Game.hpp"
#include "Vector2D.hpp"
#include "Team.hpp"

enum touchPos { UP, DOWN, LEFT, RIGHT };

const int FRAMEDECRESESPEED = 100;

class Ball {
private:
	SDL_Texture* ballTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;
	Vector2D* v;
	int needRecount;

public:
	Ball(SDL_Renderer* rend);
	~Ball();

	void Move();
	int TouchBar();
	void CheckCollideBar();
	bool InRedTeamGoal();
	bool InBlueTeamGoal();
	bool TouchPlayer(Player* player);
	void CheckCollidePlayerInTeam(Team *team);
	int GetCenterX();
	int GetCenterY();

	void Render();
};

#endif