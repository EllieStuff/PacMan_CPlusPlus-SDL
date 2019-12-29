#include "Blinky.h"

void Blinky::AddPos()
{
	switch (dir) {
	case Direction::UP:
		pos.y -= PIXELS_PER_FRAME;

		break;

	case Direction::DOWN:
		pos.y += PIXELS_PER_FRAME;

		break;

	case Direction::LEFT:
		pos.x -= PIXELS_PER_FRAME;

		break;

	case Direction::RIGHT:
		pos.x += PIXELS_PER_FRAME;

		break;

	default:;

	}

}

void Blinky::DecidePos(const Direction &forbiddenDir, std::vector<std::vector<Objects*>>o)
{
	int randNum = rand() % static_cast<int>(Direction::NONE);
	int firstNum = randNum;
	if (randNum == static_cast<int>(forbiddenDir)) {
		randNum++;
		if (randNum == static_cast<int>(Direction::NONE)) randNum = 0;

	}

	while (HitsWall(randNum, o)) {
		randNum++;
		if (randNum == static_cast<int>(Direction::NONE)) randNum = 0;

		if (firstNum == randNum) {
			dir = Direction::NONE;
			break;

		}

		if (randNum == static_cast<int>(forbiddenDir)) {
			randNum++;
			if (randNum == static_cast<int>(Direction::NONE)) randNum = 0;
		}

	}

	dir = static_cast<Direction>(randNum);
	AddPos();

}

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

void Blinky::Move(std::vector<std::vector<Objects*>> mapObjects)
{
	if (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0) {
		switch (dir) {
		case Direction::UP:
			if (pos.y < 0) 
				pos.y = SCREEN_HEIGHT - TILES_PIXEL;
			DecidePos(Direction::DOWN, mapObjects);

			break;

		case Direction::DOWN:
			if (pos.y > SCREEN_HEIGHT - TILES_PIXEL)
				pos.y = 0;
			DecidePos(Direction::UP, mapObjects);

			break;

		case Direction::LEFT:
			if (pos.x < 0)
				pos.x = SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL;
			DecidePos(Direction::RIGHT, mapObjects);

			break;

		case Direction::RIGHT:
			if (pos.x > SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL)
				pos.x = 0;
			DecidePos(Direction::LEFT, mapObjects);

			break;

		case Direction::NONE:
			if (!OnEdge()) {
				DecidePos(Direction::NONE, mapObjects);
				std::cout << "NONE\n\n";
			}

			break;

		default:;

		}
	}
	else
		AddPos();

}
