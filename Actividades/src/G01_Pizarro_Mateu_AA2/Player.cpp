#include "Player.h"


Player::Player()
{
	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 0 * frameHeight;
	rect.h = frameHeight;
	rect.w = frameWidth;

}

bool Player::OnEdge() {

	return pos.x <= 0 || pos.x >= SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL
		|| pos.y <= 0 || pos.y >= SCREEN_HEIGHT - TILES_PIXEL;
}

void Player::Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Clyde *clyde, Inky *inky, Blinky *blinky, Fruit &fruit)
{
	if (keys[SDLK_w] && (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 || dir == Direction::DOWN)
		|| (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 && goingToMove == Direction::UP)) {
		dir = Direction::UP;
		goingToMove = Direction::NONE;

	}
	if (keys[SDLK_s] && (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 || dir == Direction::UP)
		|| (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 && goingToMove == Direction::DOWN)) {
		dir = Direction::DOWN;
		goingToMove = Direction::NONE;

	}
	if (keys[SDLK_a] && (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 || dir == Direction::RIGHT)
		|| (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 && goingToMove == Direction::LEFT)) {
		dir = Direction::LEFT;
		goingToMove = Direction::NONE;

	}
	if (keys[SDLK_d] && (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 || dir == Direction::LEFT)
		|| (pos.x % TILES_PIXEL == 0 && pos.y % TILES_PIXEL == 0 && goingToMove == Direction::RIGHT)) {
		dir = Direction::RIGHT;
		goingToMove = Direction::NONE;

	}

	if (keys[SDLK_w]) goingToMove = Direction::UP;
	else if (keys[SDLK_s]) goingToMove = Direction::DOWN;
	else if (keys[SDLK_a]) goingToMove = Direction::LEFT;
	else if (keys[SDLK_d]) goingToMove = Direction::RIGHT;


	lastPos = Utils::Rect_Vec2(pos);
	if (dir == Direction::UP) {
		pos.y -= PIXELS_PER_FRAME;
		if (pos.y < 0) pos.y = SCREEN_HEIGHT - TILES_PIXEL;
		if (Hits(o, clyde, inky, blinky, fruit)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::DOWN) {
		pos.y += PIXELS_PER_FRAME;
		if (pos.y >= SCREEN_HEIGHT) pos.y = 0;
		if (Hits(o, clyde, inky, blinky, fruit)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::LEFT) {
		pos.x -= PIXELS_PER_FRAME;
		if (pos.x < 0) pos.x = SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL;
		if (Hits(o, clyde, inky, blinky, fruit)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::RIGHT) {
		pos.x += PIXELS_PER_FRAME;
		if (pos.x >= SCREEN_WIDTH - HUD_WIDTH) pos.x = 0;
		if (Hits(o, clyde, inky, blinky, fruit)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}

	FinishPowerUp(clyde, inky, blinky);
}

bool Player::Hits(std::vector<std::vector<Objects*>> &o, Clyde *clyde, Inky *inky, Blinky *blinky, Fruit &fruit)
{
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (o[i][j]->tile == MapTiles::WALL) {
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos))
					return true;
				else if (OnEdge()) {
					if (dir == Direction::UP && pos.y + SCREEN_HEIGHT - TILES_PIXEL == o[i][j]->rectPos.y
						|| dir == Direction::DOWN && pos.y - SCREEN_HEIGHT + TILES_PIXEL == o[i][j]->rectPos.y
						|| dir == Direction::LEFT && pos.x + SCREEN_WIDTH - TILES_PIXEL == o[i][j]->rectPos.x
						|| dir == Direction::RIGHT && pos.y - SCREEN_WIDTH + TILES_PIXEL == o[i][j]->rectPos.x)
						return true;
				}

			}
			if (o[i][j]->tile == MapTiles::POINTS)
			{
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos) && Utils::PointsDistance(pos, o[i][j]->rectPos) < TILES_PIXEL / 3)
				{
					score++;
					o[i][j]->tile = MapTiles::EMPTY;
					o[i][j]->rect.w = 0;
					o[i][j]->rect.h = 0;
					////return true;
				}
			}
			if (o[i][j]->tile == MapTiles::POWER_UP)
			{
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos) && Utils::PointsDistance(pos, o[i][j]->rectPos) < TILES_PIXEL / 3)
				{
					int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
					//score += POWER_UP_EXTRA_SCORE;
					o[i][j]->tile = MapTiles::EMPTY_P_UP;
					o[i][j]->rect.w = 0;
					o[i][j]->rect.h = 0;
					hasPowerUp = true;
					powerUpEnd = clock() + POWER_UP_TIME;
					clyde->rect.x = 0;
					clyde->rect.y = 4 * frameHeight;
					inky->rect.x = 0;
					inky->rect.y = 4 * frameHeight;
					blinky->rect.x = 0;
					blinky->rect.y = 4 * frameHeight;
					//return true;
				}
			}
			if (Utils::OnSquareCollision(pos, clyde->pos) && Utils::PointsDistance(pos, clyde->pos) < TILES_PIXEL / 2)
			{
				if (!hasHitEnemy && !hasPowerUp) {
					livesLeft--;
					hasHitEnemy = true;

				}
				else if (hasPowerUp) {
					score += clyde->extraScore;
					maxScore += clyde->extraScore;
					clyde->ReinitPos();

				}
				//ReinitPos();
				
			}
			if (Utils::OnSquareCollision(pos, inky->pos) && Utils::PointsDistance(pos, inky->pos) < TILES_PIXEL / 2)
			{
				if (!hasHitEnemy && !hasPowerUp) {
					livesLeft--;
					hasHitEnemy = true;

				}
				else if (hasPowerUp) {
					score += inky->extraScore;
					maxScore += inky->extraScore;
					inky->ReinitPos();

				}
				//ReinitPos();
				
			}
			if (Utils::OnSquareCollision(pos, blinky->pos) && Utils::PointsDistance(pos, blinky->pos) < TILES_PIXEL / 2)
			{
				if (!hasHitEnemy && !hasPowerUp) {
					livesLeft--;
					hasHitEnemy = true;

				}
				else if (hasPowerUp) {
					score += blinky->extraScore;
					maxScore += blinky->extraScore;
					blinky->ReinitPos();

				}
				//ReinitPos();

			}
			if (fruit.publicType != FruitTypes::EMPTY && Utils::OnSquareCollision(pos, fruit.pos) && Utils::PointsDistance(pos, fruit.pos) < TILES_PIXEL / 2) {
				score += fruit.extraScore;
				maxScore += fruit.extraScore;
				fruit.EraseFruit();

			}

			if (dead) {
				ReinitPos();
				clyde->ReinitPos();
				inky->ReinitPos();
				blinky->ReinitPos();
				dir = Direction::NONE;
				hasHitEnemy = false;
				dead = false;

			}
		}

	}
	return false;
}


void Player::Reinit(const int &_maxScore)
{
	ReinitPos();
	dir = Direction::NONE;
	rect.x = 4 * (Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8);
	rect.y = 0;
	score = 0;
	maxScore = _maxScore;
	fruits = 0;
	hasPowerUp = false;
	dead = false;
	hasHitEnemy = false;
	livesLeft = MAX_LIVES;
}
int Player::GetMaxScore()
{

	return maxScore;
}
//
//void Player::AddMaxScore(int &add)
//{
//	maxScore += score;
//
//}
//
//void Player::InitMaxScore(int &_maxScore)
//{
//	maxScore = _maxScore;
//}

void Player::FinishPowerUp(Clyde* clyde, Inky* inky, Blinky* blinky)
{
	if (powerUpEnd < clock() && hasPowerUp)
	{
		hasPowerUp = false;
		int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
		int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
		clyde->rect.x = 4 * frameWidth;
		clyde->rect.y = 3 * frameHeight;
		inky->rect.x = 4 * frameWidth;
		inky->rect.y = 2 * frameHeight;
		blinky->rect.x = 4 * frameWidth;
		blinky->rect.y = frameWidth;
	}
}

