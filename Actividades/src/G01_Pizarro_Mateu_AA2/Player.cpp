#include "Player.h"


Player::Player()
{

}

bool Player::OnEdge() {

	return pos.x <= 0 || pos.x >= SCREEN_WIDTH - HUD_WIDTH - TILES_PIXEL
		|| pos.y <= 0 || pos.y >= SCREEN_HEIGHT - TILES_PIXEL;
}

void Player::Move(std::vector<bool> keys)
{
	if (keys[SDLK_w]) { pos.y -= PIXELS_PER_FRAME; dir = Direction::UP; }
	if (keys[SDLK_s]) { pos.y += PIXELS_PER_FRAME; dir = Direction::DOWN; }
	if (keys[SDLK_a]) { pos.x -= PIXELS_PER_FRAME; dir = Direction::LEFT; }
	if (keys[SDLK_d]) { pos.x += PIXELS_PER_FRAME; dir = Direction::RIGHT; }

}

bool Player::Hits(Direction dir, std::vector<std::vector<Objects*>> o, Rect &_clydePos, Rect &_inkyPos)
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
				if (Utils::OnSquareCollision(pos, o[i][j]->rectPos))
				{
					score++;
					o[i][j]->tile == MapTiles::EMPTY;
					return true;
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
			if (pos == _clydePos)
			{
				if (Utils::OnSquareCollision(pos, _clydePos))
				{
					livesLeft--;
					ReinitPos();
					//if (livesLeft <= 0)
				}
			}
			if (pos == _inkyPos)
			{
				if (Utils::OnSquareCollision(pos, _inkyPos))
				{
					livesLeft--;
					ReinitPos();
					//if (livesLeft <= 0)
				}
			}
		}

	}
	return false;
}

bool Player::GetHasPowerUp()
{
	return false;
}

void Player::ReinitPos()
{
}

void Player::Reinit()
{
}

void Player::LecturaXMLPlayer(Renderer *_renderer)
{
	Vector2 *vec2 = new Vector2(0, 0);
	int frameWidth, frameHeight;
	_renderer->Instance();
	_renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	*vec2 = _renderer->GetTextureSize("PacmanSheet");
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
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	//Lectura XML
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



void Player::Draw(Renderer *_renderer)
{
	_renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(rect), Utils::RectToSDL_Rect(pos));
}