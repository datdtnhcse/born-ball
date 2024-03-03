#include "PlayerPole.hpp"
#include "TextureManager.hpp"

PlayerPole::PlayerPole(SDL_Renderer* rend, bool isRedTeam, int posYard, int numOfPlayers) {
	playerPoleTexture = TextureManager::LoadImage(isRedTeam?"Images/downPole.png": "Images/upPole.png", rend);
	
	renderer = rend;
	
	inRedTeam = isRedTeam;

	playersNum = numOfPlayers;

	players = new Player*[playersNum];
	switch (playersNum) {
	case 1:
		players[0] = new Player(renderer, POS2ONPOLE, posYard, inRedTeam);
		minY = isRedTeam ? -141 : -95;
		maxY = isRedTeam ? 27 : 73;
		break;
	case 2:
		players[0] = new Player(renderer, POS1ONPOLE, posYard, inRedTeam);
		players[1] = new Player(renderer, POS3ONPOLE, posYard, inRedTeam);
		minY = isRedTeam ? -141 : -95;
		maxY = isRedTeam ? 27 : 73;
		break;
	case 3:
		players[0] = new Player(renderer, POS1ONPOLE, posYard, inRedTeam);
		players[1] = new Player(renderer, POS2ONPOLE, posYard, inRedTeam);
		players[2] = new Player(renderer, POS3ONPOLE, posYard, inRedTeam);
		minY = isRedTeam ? -141 : -95;
		maxY = isRedTeam ? 27 : 73;
		break;
	default:
		players[0] = new Player(renderer, POS0ONPOLE, posYard, inRedTeam);
		players[1] = new Player(renderer, POS1ONPOLE, posYard, inRedTeam);
		players[2] = new Player(renderer, POS2ONPOLE, posYard, inRedTeam);
		players[3] = new Player(renderer, POS3ONPOLE, posYard, inRedTeam);
		players[4] = new Player(renderer, POS4ONPOLE, posYard, inRedTeam);
		minY = isRedTeam ? -82 : -36;
		maxY = isRedTeam ? -32 : 14;
		break;
	}

	dstRect.x = posYard;
	dstRect.y = isRedTeam ? -57 : -11;
	dstRect.w = 13;
	dstRect.h = 668;
}

PlayerPole::~PlayerPole() {}

Player** PlayerPole::GetPlayers() {
	return players;
}

int PlayerPole::GetPlayersNum() {
	return playersNum;
}

void PlayerPole::Move(int distance) {
	if (distance == 0) {
		return;
	}

	int playerMoveDistance = 0;

	if (distance < 0) {
		playerMoveDistance = dstRect.y + distance < minY ? minY - dstRect.y : distance;
		dstRect.y = dstRect.y + distance < minY ? minY : dstRect.y + distance;
	}
	else {
		playerMoveDistance = dstRect.y + distance > maxY ? maxY - dstRect.y : distance;
		dstRect.y = dstRect.y + distance > maxY ? maxY : dstRect.y + distance;
	}

	for (int i = 0; i < playersNum; i++) {
		players[i]->Move(playerMoveDistance);
	}
}

void PlayerPole::Render() {
	SDL_RenderCopy(renderer, playerPoleTexture, NULL, &dstRect);
	for (int i = 0; i < playersNum; i++) {
		players[i]->Render();
	}
}