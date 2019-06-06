#pragma once
#include "GameController.h"
#include "Level1.h"


void Level1::Load() {

	y = 0;
	y_speed = 0;

	wchar_t f[] = L"sample.bmp";

	mySprites = new SpriteSheet(f, g);

	tile = new SpriteSheet((wchar_t *)L"ts.png", g, 34);

}


void Level1::Unload() {

	delete mySprites;

}


void Level1::Update() {

	//Update logic
	y_speed += GRAVITY;
	y += y_speed;

	if (y > GameController::GetHeight()) {

		y = GameController::GetHeight();
		y_speed = -30.0f;

	}

}

void Level1::Render() {

	//Rendering Logic		
	g->Fill(255, 255, 255, 1);

	mySprites->Draw();	

	WCHAR f[4];
	
	_itow((int)y, f, 10);	

	g->Text(f , sizeof(f) / sizeof (f[0]) , 50, 50, GameController::GetWidth(), GameController::GetHeight());

	g->DrawCircle(GameController::GetWidth() / 2, y, 10, 4.0f);

}
