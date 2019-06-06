#pragma once
#include <wincodec.h>
#include <vector>
#include "Graphics.h"

class SpriteSheet
{
	Graphics * g;
	ID2D1Bitmap * bmp;
	int height, width;
	int spritesAcrossH, spritesAcrossV;
	int spriteSize;

public:

	SpriteSheet(wchar_t * filename, Graphics* gfx);

	SpriteSheet(wchar_t * f, Graphics * gfx, int size);

	~SpriteSheet();

	void Draw();

	void Draw(int row, int col, int x, int y);
};

