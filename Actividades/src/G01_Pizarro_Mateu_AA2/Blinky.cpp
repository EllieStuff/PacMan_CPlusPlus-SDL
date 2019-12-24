#include "Blinky.h"

Blinky::Blinky()
{
	extraScore = 25;

	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 1 * frameHeight;
	rect.h = frameHeight;
	rect.w = frameWidth;

}

void Blinky::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	
}
