#include "Player.hpp"
#include "TextureManager.hpp"

Player::Player(SDL_Renderer* rend, int posPole, int posYard, bool isRedTeam) {
	renderer = rend;

	playerTexture = TextureManager::LoadImage(isRedTeam ? "Images/redPlayer.png" : "Images/bluePlayer.png", renderer);
	
	dstRect.x = posYard - 2;
	dstRect.y = posPole;
	dstRect.w = 17;
	dstRect.h = 30;

	posPoleOnYard = posYard;

	inRedTeam = isRedTeam;

	action = NORMAL;
	actionSteps = 0;
}

Player::~Player() {}

void Player::Move(int distance) {
	dstRect.y += distance;
}

void Player::KickLeft() {
	dstRect.x = posPoleOnYard - 15;
	dstRect.w = 41;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(inRedTeam ? "Images/redPlayerKickLeft.png" : "Images/bluePlayerKickLeft.png", renderer);
}

void Player::KickRight() {
	dstRect.x = posPoleOnYard - 10;
	dstRect.w = 41;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(inRedTeam ? "Images/redPlayerKickRight.png" : "Images/bluePlayerKickRight.png", renderer);
}

void Player::Normal() {
	dstRect.x = posPoleOnYard - 2;
	dstRect.w = 17;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(inRedTeam ? "Images/redPlayer.png" : "Images/bluePlayer.png", renderer);
}

SDL_Rect Player::GetRect() {
	return dstRect;
}

int Player::CountSqrDistance(int ballX, int ballY) {
	return (dstRect.x + 8 - ballX) * (dstRect.x + 8 - ballX) + (dstRect.y + 15 - ballY) * (dstRect.y + 15 - ballY);
}

void Player::SetAction(int act) {
	action = act;
	switch (act) {
	case KICKLEFT:
		actionSteps = 1;
		break;
	case KICKRIGHT:
		actionSteps = 1;
		break;
	case LEFT2RIGHT:
		actionSteps = 2;
		break;
	case RIGHT2LEFT:
		actionSteps = 2;
		break;
	default:
		actionSteps = 0;
	}
}

void Player::Render() {
	if (actionSteps == 0) action = NORMAL;
	if (action == NORMAL) {
		Normal();
	}
	else {
		switch (action) {
		case KICKLEFT:
			KickLeft();
			break;
		case KICKRIGHT:
			KickRight();
			break;
		case LEFT2RIGHT:
			switch (actionSteps) {
			case 2:
				KickLeft();
				break;
			case 1:
				KickRight();
				break;
			}
			break;
		case RIGHT2LEFT:
			switch (actionSteps) {
			case 2:
				KickRight();
				break;
			case 1:
				KickLeft();
				break;
			}
			break;
		}
		actionSteps -= 1;
	}
	SDL_RenderCopy(renderer, playerTexture, NULL, &dstRect);
}