#include "GameController.h"

GameLevel * GameController::currentLevel;

bool  GameController::Loading;

int GameController::WIDTH;

int GameController::HEIGHT;

void GameController::Init(int w, int h) {

	HEIGHT = h, WIDTH = w;

	Loading = true;

	currentLevel = 0;

}

void GameController::LoadInitialLevel(GameLevel* lev) {

	Loading = true;

	currentLevel = lev;

	currentLevel->Load();

	Loading = false;

}

void GameController::SwitchLevel(GameLevel * lev) {

	Loading = true;

	currentLevel->Unload();

	lev->Load();

	delete currentLevel;

	currentLevel = lev;

	Loading = false;

}

void GameController::Render() {

	if (Loading) return;

	currentLevel->Render();

}

void GameController::Update() {

	if (Loading) return;

	currentLevel->Update();

}