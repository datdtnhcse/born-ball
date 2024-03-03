#include "Bot.hpp"

Bot::Bot(Team* team) {
	controlTeam = team;
	needMoveDistance = 0;
	needRecount = FRAMEBOTRECOUNT;
}

Bot::~Bot() {}

void Bot::MovePole() {
	if (needRecount > 0) {
		needRecount--;
		return;
	}
	if (needMoveDistance == 0) return;
	controlTeam->Move(needMoveDistance > 0 ? MOVE_STEP : -MOVE_STEP);
	needMoveDistance -= needMoveDistance > 0 ? MOVE_STEP : -MOVE_STEP;
	needRecount = FRAMEBOTRECOUNT;
}

void Bot::UpdateWill(int ballX, int ballY) {
	PlayerPole** poles = controlTeam->GetPlayerPoles();
	Player* nearestPlayer = nullptr;
	int minSqrDistance = 99999999;
	for (int i = 0; i < 4; i++) {
		Player** players = poles[i]->GetPlayers();
		for (int j = 0; j < poles[i]->GetPlayersNum(); j++) {
			int d = players[j]->CountSqrDistance(ballX, ballY);
			if (d < minSqrDistance) {
				nearestPlayer = players[j];
				minSqrDistance = d;
			}
		}
	}

	needMoveDistance = nearestPlayer ? ballY - nearestPlayer->GetRect().y - 15 : 0;
}


