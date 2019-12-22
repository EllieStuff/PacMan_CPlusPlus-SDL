#include "Player.h"


Player::Player()
{

}

bool Player::OnEdge() {

	return pos.x <= 0 || pos.x >= SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL
		|| pos.y <= 0 || pos.y >= SCREEN_HEIGHT - TILES_PIXEL;
}

void Player::Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Clyde *clyde, Inky *inky)
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
		if (Hits(o, clyde, inky)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::DOWN) {
		pos.y += PIXELS_PER_FRAME;
		if (pos.y >= SCREEN_HEIGHT) pos.y = 0;
		if (Hits(o, clyde, inky)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::LEFT) {
		pos.x -= PIXELS_PER_FRAME;
		if (pos.x < 0) pos.x = SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL;
		if (Hits(o, clyde, inky)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}
	if (dir == Direction::RIGHT) {
		pos.x += PIXELS_PER_FRAME;
		if (pos.x >= SCREEN_WIDTH - HUD_WIDTH) pos.x = 0;
		if (Hits(o, clyde, inky)) {
			pos.x = lastPos.x;
			pos.y = lastPos.y;

		}
	}

}

bool Player::Hits(std::vector<std::vector<Objects*>> &o, Clyde *clyde, Inky *inky)
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
			/*if (o[i][j]->tile == MapTiles::FRUIT)
			{
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos))
				{
					o[i][j]->tile == MapTiles::EMPTY;
					return true;
				}
			}
			if (o[i][j]->tile == MapTiles::POWER_UP)
			{
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos))
				{
					o[i][j]->tile == MapTiles::EMPTY;
					return true;
				}
			}*/
			if (Utils::OnSquareCollision(pos, clyde->pos) && Utils::PointsDistance(pos, clyde->pos) < TILES_PIXEL / 2)
			{
				if (!hasHitEnemy) {
					livesLeft--;
					hasHitEnemy = true;

				}
				//ReinitPos();
				
			}
			if (Utils::OnSquareCollision(pos, inky->pos) && Utils::PointsDistance(pos, inky->pos) < TILES_PIXEL / 2)
			{
				if (!hasHitEnemy) {
					livesLeft--;
					hasHitEnemy = true;

				}
				//ReinitPos();
				
			}
			if (dead) {
				ReinitPos();
				clyde->ReinitPos();
				inky->ReinitPos();
				dir = Direction::NONE;
				hasHitEnemy = false;
				dead = false;

			}
		}

	}
	return false;
}


bool Player::GetHasPowerUp()
{
	return false;
}

void Player::Reinit()
{
	ReinitPos();
	dir = Direction::NONE;
	rect.x = 4 * (Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8);
	rect.y = 0;
	score = 0;
	fruits = 0;
	hasPowerUp = false;
	dead = false;
	hasHitEnemy = false;
	livesLeft = MAX_LIVES;
}

void Player::LecturaXMLPlayer()
{
	Vector2 *vec2 = new Vector2(0, 0);
	int frameWidth, frameHeight;
	*vec2 = Renderer::Instance()->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 0 * frameHeight;
	pos.h = TILES_PIXEL;
	rect.h = frameHeight;
	pos.w = TILES_PIXEL;
	rect.w = frameWidth;
	std::string numX, numY;
	int x, y;

	//Lectura XML
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *pNode = pRoot->first_node("Positions");
	rapidxml::xml_node<> *pNodeI = pNode->first_node();
	rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute();
	numX = pAttr->value();
	pAttr = pAttr->next_attribute();
	numY = pAttr->value();
	x = std::stoi(numX) - 1;
	y = std::stoi(numY) - 1;
	pos.x = x * TILES_PIXEL;
	pos.y = y * TILES_PIXEL;
	initialPos.x = pos.x;
	initialPos.y = pos.y;
}

void Player::Draw()
{
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(rect), Utils::RectToSDL_Rect(pos));
}