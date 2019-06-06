#pragma once
#include "GameController.h"
#include "Level2.h"
#include <stdlib.h>

void Level2::Load() {

	//im(L"sample.bmp");

}

void Level2::Unload() {

	

}

void Level2::Update() {

	


}

void Level2::Render() {

	//int y = rand() % im.GetHeight();

	//int x = rand() % im.GetWidth();

	//c.GetR(), c.GetG(), c.GetB(), c.GetA()

	//c = im.Read(x , y);

	g->Fill(255, 0, 0, 1);

	g->DrawCircle(GameController::GetWidth()/2, GameController::GetHeight()/2, 10, 5.0f);

}
