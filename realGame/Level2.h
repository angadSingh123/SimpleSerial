#include "GameLevel.h"
#include "ImageReader.h"

class Level2 : public GameLevel {

public:

	void Load() override;

	void Unload() override;

	void Render() override;

	void Update() override;

};