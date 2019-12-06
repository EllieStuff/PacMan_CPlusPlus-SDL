#include "Enemies.h"

bool OnSquareCollision(const Rect &avatar, const Rect &square) {

	return avatar.x > square.x && avatar.x < square.x + square.w
		&& avatar.y > square.y && avatar.y < square.y + square.h;
}

bool Enemies::OnEdge() {

	return pos.x <= 0 || pos.x >= SCREEN_WIDTH - HUD_WIDTH - TILE_SIZE
		|| pos.y <= 0 || pos.y >= SCREEN_HEIGHT - TILE_SIZE;
}


bool Enemies::HitsWall(Direction playerDir, std::vector<std::vector<Objects*>> o)
{
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (o[i][j]->tile == MapTiles::WALL) {
				if (OnSquareCollision(pos, o[i][j]->pos))
					return true;
				else if (OnEdge()) {
					if (playerDir == Direction::UP && pos.y + SCREEN_HEIGHT - TILE_SIZE == o[i][j]->pos.y
						|| playerDir == Direction::DOWN && pos.y - SCREEN_HEIGHT + TILE_SIZE == o[i][j]->pos.y
						|| playerDir == Direction::LEFT && pos.x + SCREEN_WIDTH - TILE_SIZE == o[i][j]->pos.x
						|| playerDir == Direction::RIGHT && pos.y - SCREEN_WIDTH + TILE_SIZE == o[i][j]->pos.x)
						return true;

				}

			}
		}

	}

	return false;
}
