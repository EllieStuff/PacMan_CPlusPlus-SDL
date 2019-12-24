#include "Clyde.h"



Clyde::Clyde()
{
	extraScore = 15;

	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 3 * frameHeight;
	rect.h = frameHeight;
	rect.w = frameWidth;

}

void Clyde::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	if (playerDir == Direction::UP && pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) 
		dir = Direction::DOWN;
	else if (playerDir == Direction::DOWN && pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) 
		dir = Direction::UP;
	else if (playerDir == Direction::LEFT && pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) 
		dir = Direction::RIGHT;
	else if (playerDir == Direction::RIGHT && pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) 
		dir = Direction::LEFT;

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

	default:;

	}

}
