#include "Blinky.h"

void Blinky::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	Direction enemyDir;
	if (playerDir == Direction::UP) enemyDir = Direction::DOWN;
	else if (playerDir == Direction::DOWN) enemyDir = Direction::UP;
	else if (playerDir == Direction::LEFT) enemyDir = Direction::RIGHT;
	else enemyDir = Direction::LEFT;

	if (!HitsWall(playerDir, mapObjects)) {
		switch (playerDir) {
		case Direction::UP:
			pos.y -= PIXELS_PER_FRAME;	//5 pixels
			if (pos.y < 0) pos.y = SCREEN_HEIGHT - TILES_PIXEL;

			break;

		case Direction::DOWN:
			pos.y += PIXELS_PER_FRAME;
			if (pos.y >= SCREEN_HEIGHT) pos.y = 0;

			break;

		case Direction::LEFT:
			pos.x -= PIXELS_PER_FRAME;
			if (pos.x < 0) pos.x = SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL;

			break;

		case Direction::RIGHT:
			pos.x += PIXELS_PER_FRAME;
			if (pos.x >= SCREEN_WIDTH - HUD_WIDTH) pos.x = 0;

			break;

		default:;

		}
	}

}
