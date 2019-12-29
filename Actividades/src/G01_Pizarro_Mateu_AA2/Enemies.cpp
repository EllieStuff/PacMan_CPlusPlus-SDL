#include "Enemies.h"


bool Enemies::OnEdge() {

	return pos.x <= 0 || pos.x >= SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL
		|| pos.y <= 0 || pos.y >= SCREEN_HEIGHT - TILES_PIXEL;
}

void Enemies::Reinit()
{
}

void Enemies::Update(Direction, Map)
{
}




Enemies::Enemies()
{

}

void Enemies::Move(Direction, std::vector<std::vector<Objects*>>)
{
}

void Enemies::Move(std::vector<std::vector<Objects*>>)
{

}

bool Enemies::HitsWall(Direction playerDir, std::vector<std::vector<Objects*>> o)
{
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (o[i][j]->tile == MapTiles::WALL) {
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos))
					return true;
				else if (OnEdge()) {
					if (playerDir == Direction::UP && pos.y + SCREEN_HEIGHT - TILES_PIXEL == o[i][j]->rectPos.y
						|| playerDir == Direction::DOWN && pos.y - SCREEN_HEIGHT + TILES_PIXEL == o[i][j]->rectPos.y
						|| playerDir == Direction::LEFT && pos.x + SCREEN_WIDTH - TILES_PIXEL == o[i][j]->rectPos.x
						|| playerDir == Direction::RIGHT && pos.y - SCREEN_WIDTH + TILES_PIXEL == o[i][j]->rectPos.x)
						return true;

				}

			}
		}

	}

	return false;
}

bool Enemies::HitsWall(const int &dirN, std::vector<std::vector<Objects*>> o)
{
	Rect tmpPos = pos;
	switch (static_cast<Direction>(dirN)) {
	case Direction::UP:
		tmpPos.y -= PIXELS_PER_FRAME;

		break;

	case Direction::DOWN:
		tmpPos.y += PIXELS_PER_FRAME;

		break;

	case Direction::LEFT:
		tmpPos.x -= PIXELS_PER_FRAME;

		break;

	case Direction::RIGHT:
		tmpPos.x += PIXELS_PER_FRAME;

		break;

	default:;

	}
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (o[j][i]->tile == MapTiles::WALL) {
				if (Utils::OnSquareCollision(tmpPos, o[j][i]->rectPos))
					return true;

			}
		}

	}

	return false;
}

void Enemies::LecturaXMLEnemy()
{
}
