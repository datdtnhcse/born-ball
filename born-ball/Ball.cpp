#include "Ball.hpp"
#include "TextureManager.hpp"

int sqr(int x) {
	return x * x;
}

Vector2D* playerKickV = new Vector2D(1, 0);

Ball::Ball(SDL_Renderer* rend) {
	renderer = rend;

	ballTexture = TextureManager::LoadImage("Images/ball.png", renderer);

	dstRect.x = 500 - BALL_RADIUS;
	dstRect.y = 400 - BALL_RADIUS;
	dstRect.w = BALL_RADIUS * 2;
	dstRect.h = BALL_RADIUS * 2;

	v = new Vector2D(1, 3);

	needRecount = FRAMEDECRESESPEED;
}

Ball::~Ball() {}

void Ball::Move() {
	if (needRecount == 0) {
		v->x = v->x * 4 / 5;
		v->y = v->y * 4 / 5;
		needRecount = FRAMEDECRESESPEED;
	} else {
		needRecount -= 1;
	}

	if (dstRect.y + v->y >= 216 && dstRect.y + v->y + BALL_RADIUS * 2 <= 384) {
		dstRect.x += v->x;
		dstRect.y += v->y;
		return;
	}
	dstRect.x = dstRect.x + v->x - 100 < 0 ? 100 : 900 - dstRect.x - v->x < BALL_RADIUS * 2 ? 900 - BALL_RADIUS * 2 : dstRect.x + v->x;
	dstRect.y = dstRect.y + v->y - 100 < 0 ? 100 : 500 - dstRect.y - v->y < BALL_RADIUS * 2 ? 500 - BALL_RADIUS * 2 : dstRect.y + v->y;
}

int Ball::TouchBar() {
	if (dstRect.x - 100 == 0 && (dstRect.y + BALL_RADIUS <= 216 || dstRect.y - BALL_RADIUS >= 384)) {
		return LEFT;
	}
	if (900 - dstRect.x == BALL_RADIUS * 2 && (dstRect.y + BALL_RADIUS <= 216 || dstRect.y - BALL_RADIUS >= 384)) {
		return RIGHT;
	}
	if (dstRect.y - 100 == 0) {
		return UP;
	}
	if (500 - dstRect.y == BALL_RADIUS * 2) {
		return DOWN;
	}
	return -1;
}

void Ball::CheckCollideBar() {
	int pos = TouchBar();
	if (pos == -1) return;

	Vector2D* n = nullptr;

	switch(pos) {
	case UP:
		n = new Vector2D(0, 1);
		break;
	case DOWN:
		n = new Vector2D(0, -1);
		break;
	case LEFT:
		n = new Vector2D(1, 0);
		break;
	case RIGHT:
		n = new Vector2D(-1, 0);
		break;
	}

	v = *v - n->MUL(v->DOT(n))->MUL(2);
}

bool Ball::InBlueTeamGoal() {
	return dstRect.x + 11 <= 100;
}

bool Ball::InRedTeamGoal() {
	return dstRect.x + 11 >= 900;
}

bool Ball::TouchPlayer(Player* player) {
	SDL_Rect playerRect = player->GetRect();

	int x = dstRect.x + BALL_RADIUS;
	int y = dstRect.y + BALL_RADIUS;

	if (sqr(x - playerRect.x) + sqr(y - playerRect.y) <= sqr(BALL_RADIUS)) return true;
	if (sqr(x - playerRect.x - playerRect.w) + sqr(y - playerRect.y) <= sqr(BALL_RADIUS)) return true;
	if (sqr(x - playerRect.x) + sqr(y - playerRect.y - playerRect.h) <= sqr(BALL_RADIUS)) return true;
	if (sqr(x - playerRect.x - playerRect.w) + sqr(y - playerRect.y - playerRect.h) <= sqr(BALL_RADIUS)) return true;

	if (x >= playerRect.x && x <= playerRect.x + playerRect.w) {
		if (playerRect.y > y) {
			return playerRect.y - y <= BALL_RADIUS;
		}
		if (playerRect.y + playerRect.h < y) {
			return y - playerRect.y - playerRect.h <= BALL_RADIUS;
		}
		return false;
	}
	if (y >= playerRect.y && y <= playerRect.y + playerRect.h) {
		if (playerRect.x > x) {
			return playerRect.x - x <= BALL_RADIUS;
		}
		if (playerRect.x + playerRect.w < x) {
			return x - playerRect.x - playerRect.w <= BALL_RADIUS;
		}
		return false;
	}
	
	return false;
}

void Ball::CheckCollidePlayerInTeam(Team* team) {
	PlayerPole **playerpoles = team->GetPlayerPoles();
	Player *collidedPlayer = nullptr;
	
	for (int i = 0; i < 4; i++) {
		Player **players = playerpoles[i]->GetPlayers();
		for (int j = 0; j < playerpoles[i]->GetPlayersNum(); j++) {
			if (TouchPlayer(players[j])) {
				collidedPlayer = players[j];
				break;
			}
		}
		if (collidedPlayer) break;
	}

	if (!collidedPlayer) return;

	if (team->OnLeftSide()) {
		if (v->x < 0) {
			Vector2D* n = new Vector2D(1,0);
			v = *(*v - n->MUL(v->DOT(n))->MUL(2)) + playerKickV;
			collidedPlayer->SetAction(KICKRIGHT);
		}
		else {
			collidedPlayer->SetAction(LEFT2RIGHT);
			v = *v + playerKickV;
		}
	}
	else {
		if (v->x > 0) {
			collidedPlayer->SetAction(KICKLEFT);
			Vector2D* n = new Vector2D(-1, 0);
			v = *(*v - n->MUL(v->DOT(n))->MUL(2)) - playerKickV;
		}
		else {
			collidedPlayer->SetAction(RIGHT2LEFT);
			v = *v - playerKickV;
		}
	}
}

int Ball::GetCenterX() {
	return dstRect.x + BALL_RADIUS;
}

int Ball::GetCenterY() {
	return dstRect.y + BALL_RADIUS;
}

void Ball::Render() {
	SDL_RenderCopy(renderer, ballTexture, NULL, &dstRect);
}