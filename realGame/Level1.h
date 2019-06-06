#pragma once
#include "GameLevel.h"

class Level1 : public GameLevel {

	const float GRAVITY = 1.0f;
	float y = 0;
	float y_speed = 0;
	SpriteSheet * mySprites, *tile;

public:

	void Load() override;

	void Unload() override;

	void Render() override;

	void Update() override;

};


