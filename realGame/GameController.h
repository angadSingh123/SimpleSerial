#pragma once
#include "GameLevel.h"

/* This class controls each of the game level instances.


*/
class GameController {

	GameController() {}

	static GameLevel* currentLevel;

	static bool Loading;

	static int WIDTH;

	static int HEIGHT;

public:

	static void Init(int, int);

	static void LoadInitialLevel(GameLevel * lev);

	static void SwitchLevel(GameLevel * lev);

	static void Render();

	static void Update();

	inline static int GetHeight() { return HEIGHT; }

	inline static int GetWidth() { return WIDTH; }

};


