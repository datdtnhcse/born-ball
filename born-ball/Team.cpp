#include "Team.hpp"
#include "TextureManager.hpp"

Team::Team(SDL_Renderer* rend, bool leftSide) {
	onLeftSide = leftSide;
	score = 0;

	if (leftSide) {
		playerPoles[0] = new PlayerPole(rend, false, POS0ONYARD, 1);
		playerPoles[1] = new PlayerPole(rend, false, POS1ONYARD, 2);
		playerPoles[2] = new PlayerPole(rend, false, POS3ONYARD, 5);
		playerPoles[3] = new PlayerPole(rend, false, POS5ONYARD, 3);
	}
	else {
		playerPoles[0] = new PlayerPole(rend, true, POS2ONYARD, 3);
		playerPoles[1] = new PlayerPole(rend, true, POS4ONYARD, 5);
		playerPoles[2] = new PlayerPole(rend, true, POS6ONYARD, 2);
		playerPoles[3] = new PlayerPole(rend, true, POS7ONYARD, 1);
	}
}

Team::~Team() {}

void Team::Move(int distance) {
	for (int i = 0; i < 4; i++) {
		playerPoles[i]->Move(distance);
	}
}

void Team::AddScore() {
	score += 1;
}

int Team::GetScore() {
	return score;
}

bool Team::OnLeftSide() {
	return onLeftSide;
}

PlayerPole** Team::GetPlayerPoles() {
	return playerPoles;
}

void Team::Render() {
	for (int i = 0; i < 4; i++) {
		playerPoles[i]->Render();
	}
}