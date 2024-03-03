#include "Game.hpp"
#include "TextureManager.hpp"
#include "Yard.hpp"
#include "BlockBars.hpp"
#include "Team.hpp"
#include "Ball.hpp"
#include "Bot.hpp"

Game::Game() {}

Game::~Game() {}

Yard *yard;
BlockBars *bars;
Team *blueTeam, *redTeam;
Ball *ball;
Bot* bot;

SDL_Rect popupRect, blurRect;
SDL_Color red = { 224, 27, 27 }, blue = { 255, 255, 255 };

// Score
const char* score[8] = {"0", "1", "2", "3", "4", "5", "6", "7"};
TTF_Font* font = nullptr;
SDL_Texture *redScoreTexture, *blueScoreTexture, *endTexture, *pauseTextture;
SDL_Rect redScoreRect, blueScoreRect;

// End Game
SDL_Rect winTextureRect;
SDL_Texture *winTexture;

// Menu
SDL_Rect menuTextureRect;
SDL_Texture* menuTexture;

void Game::init(const char* title, int w, int h) {	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || !font) run = false;
	
	std::cout << "Subsystem initialized..." << std::endl;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (window) {
		std::cout << "Window created..." << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		std::cout << "Renderer created..." << std::endl;
	}

	TTF_Init();
	font = TTF_OpenFont("Fonts/pixel-gaming-font/PixelGamingRegular-d9w0g.ttf", 30);

	run = true;

	yard = new Yard(renderer);

	bars = new BlockBars(renderer);

	blurRect.x = 0;
	blurRect.y = 0;
	blurRect.w = 1000;
	blurRect.h = 600;

	popupRect.x = 300;
	popupRect.y = 200;
	popupRect.w = 400;
	popupRect.h = 200;
}

void Game::start() {
	if (blueTeam) blueTeam->~Team();
	if (redTeam) redTeam->~Team();
	if (ball) ball->~Ball();
	if (bot) bot->~Bot();

	blueTeam = new Team(renderer, true);
	redTeam = new Team(renderer, false);

	if (state == PLAYWITHBOT) bot = new Bot(redTeam);

	ball = new Ball(renderer);

	redScoreRect.x = 520;
	redScoreRect.y = 10;
	redScoreRect.w = 30;
	redScoreRect.h = 40;

	blueScoreRect.x = 455;
	blueScoreRect.y = 10;
	blueScoreRect.w = 30;
	blueScoreRect.h = 40;

	redScoreTexture = TextureManager::LoadText(score[redTeam->GetScore()], renderer, blue, font);
	blueScoreTexture = TextureManager::LoadText(score[blueTeam->GetScore()], renderer, blue, font);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		run = false;
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) state = MENU;

	switch (state)
	{
	case END:
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) state = MENU;
		break;
	case MENU:
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_1) state = PLAYWITHPERSON;
			if (event.key.keysym.sym == SDLK_2) state = PLAYWITHBOT;
			start();
		}
		break;
	case PLAYWITHPERSON:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				redTeam->Move(-MOVE_STEP);
				break;
			case SDLK_DOWN:
				redTeam->Move(MOVE_STEP);
				break;
			case SDLK_w:
				blueTeam->Move(-MOVE_STEP);
				break;
			case SDLK_s:
				blueTeam->Move(MOVE_STEP);
				break;
			}
		}
		break;
	default:
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				blueTeam->Move(-MOVE_STEP);
				break;
			case SDLK_DOWN:
				blueTeam->Move(MOVE_STEP);
				break;
			}
		}
	}
}

void Game::update() {
	if (ball->InRedTeamGoal()) {
		blueTeam->AddScore();
		blueScoreTexture = TextureManager::LoadText(score[blueTeam->GetScore()], renderer, blue, font);
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}
	if (ball->InBlueTeamGoal()) {
		redTeam->AddScore();
		redScoreTexture = TextureManager::LoadText(score[redTeam->GetScore()], renderer, red, font);
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}

	if (state == PLAYWITHBOT) {
		bot->UpdateWill(ball->GetCenterX(), ball->GetCenterY());
		bot->MovePole();
	}

	ball->CheckCollideBar();
	ball->CheckCollidePlayerInTeam(redTeam);
	ball->CheckCollidePlayerInTeam(blueTeam);

	ball->Move();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 158, 43, 8, 255);
	SDL_RenderClear(renderer);

	yard->Render();

	ball->Render();

	blueTeam->Render();
	redTeam->Render();

	bars->Render();

	SDL_RenderCopy(renderer, redScoreTexture, nullptr, &redScoreRect);
	SDL_RenderCopy(renderer, blueScoreTexture, nullptr, &blueScoreRect);

	if (state == END) {
		renderEndScreen();
	}

	SDL_RenderPresent(renderer);
}

void Game::renderEndScreen() {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 140);
	SDL_RenderFillRect(renderer, &blurRect);
	
	SDL_SetRenderDrawColor(renderer, 117, 125, 117, 255);
	SDL_RenderFillRect(renderer, &popupRect);
	
	winTexture = TextureManager::LoadText("win!", renderer, { 0, 0, 0 }, font);
	winTextureRect.x = 510;
	winTextureRect.y = 250;
	winTextureRect.w = 80;
	winTextureRect.h = 50;
	SDL_RenderCopy(renderer, winTexture, nullptr, &winTextureRect);
	
	winTexture = TextureManager::LoadText(blueTeam->GetScore() == 7 ? "Blue" : "Red", renderer, blueTeam->GetScore() == 7 ? blue : red, font);
	winTextureRect.x = 410;
	SDL_RenderCopy(renderer, winTexture, nullptr, &winTextureRect);
	
	redScoreRect.y = 300;
	blueScoreRect.y = 300;
	SDL_RenderCopy(renderer, redScoreTexture, nullptr, &redScoreRect);
	SDL_RenderCopy(renderer, blueScoreTexture, nullptr, &blueScoreRect);
}

void Game::renderMenuScreen() {
	SDL_SetRenderDrawColor(renderer, 99, 13, 13, 255);
	SDL_RenderClear(renderer);

	menuTexture = TextureManager::LoadText("Play with other person: Press 1", renderer, { 209, 227, 95 }, font);
	menuTextureRect.x = 280;
	menuTextureRect.y = 200;
	menuTextureRect.w = 450;
	menuTextureRect.h = 50;
	SDL_RenderCopy(renderer, menuTexture, nullptr, &menuTextureRect);
	menuTexture = TextureManager::LoadText("Play with bot             : Press 2", renderer, { 209, 227, 95 }, font);
	menuTextureRect.y = 250;
	menuTextureRect.w = 450;
	SDL_RenderCopy(renderer, menuTexture, nullptr, &menuTextureRect);

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::checkGameEnd() {
	if (blueTeam->GetScore() == 7) {
		state = END;
		return;
	}
	if (redTeam->GetScore() == 7) {
		state = END;
		return;
	}
}

bool Game::running() {
	return run;
}
