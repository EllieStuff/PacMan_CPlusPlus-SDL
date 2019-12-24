#include "Inky.h"

Inky::Inky()
{
	extraScore = 10;

	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 2 * frameHeight;
	rect.h = frameHeight;
	rect.w = frameWidth;

}

void Inky::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	if(pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) dir = playerDir;
	lastPos = Utils::Rect_Vec2(pos);
	switch (dir) {
	case Direction::UP:
		pos.y -= PIXELS_PER_FRAME;	//5 pixels
		if (pos.y < 0) pos.y = SCREEN_HEIGHT - TILES_PIXEL;
		if (HitsWall(dir, mapObjects)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}

		break;

	case Direction::DOWN:
		pos.y += PIXELS_PER_FRAME;
		if (pos.y >= SCREEN_HEIGHT) pos.y = 0;
		if (HitsWall(dir, mapObjects)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}

		break;

	case Direction::LEFT:
		pos.x -= PIXELS_PER_FRAME;
		if (pos.x < 0) pos.x = SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL;
		if (HitsWall(dir, mapObjects)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}

		break;

	case Direction::RIGHT:
		pos.x += PIXELS_PER_FRAME;
		if (pos.x >= SCREEN_WIDTH - HUD_WIDTH) pos.x = 0;
		if (HitsWall(dir, mapObjects)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}

		break;

	default:
		break;

	}

}
