#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class GameLevel {

	/* An abstract class that can be instatnitaited per level, and provides helpful functions for loading and displaying the level


	*/

public:

	static void Init(Graphics * gf) {

		g = gf;

	}

	virtual void Load() = 0;

	virtual void Unload() = 0;

	virtual void Render() = 0;

	virtual void  Update() = 0;	

private:


protected:

	static Graphics * g;
	
};