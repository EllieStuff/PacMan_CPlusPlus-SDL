#include "Player.h"


void Player::Move(std::vector<bool> keys)
{
	if (keys[SDLK_w]) pos.y -= PIXELS_PER_FRAME;
	if (keys[SDLK_s]) pos.y += PIXELS_PER_FRAME;
	if (keys[SDLK_a]) pos.x -= PIXELS_PER_FRAME;
	if (keys[SDLK_d]) pos.x += PIXELS_PER_FRAME;

}

bool Player::HitsWall(Direction dir, std::vector<std::vector<Objects*>> o)
{


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
	rect.h = TILES_PIXEL;
	rect.h = frameHeight;
	pos.w = TILES_PIXEL;
	pos.w = frameWidth;
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
	rapidxml::xml_node<> *pNode = pRoot->first_node("Player");
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
	numX = pAttr->value();
	pAttr = pAttr->next_attribute();
	numY = pAttr->value();
	x = std::stoi(numX) - 1;
	y = std::stoi(numY) - 1;
	pos.x = x * TILES_PIXEL;
	pos.y = y * TILES_PIXEL;
}



void Player::Draw(Renderer *_renderer)
{
	_renderer->PushSprite("PacmanSheet", RectToSDL_Rect(rect), RectToSDL_Rect(pos));
}