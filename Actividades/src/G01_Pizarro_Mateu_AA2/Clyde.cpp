#include "Clyde.h"



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

void Clyde::LecturaXMLEnemy(Renderer* _renderer)
{
	Vector2 *vec2 = new Vector2(0, 0);
	int frameWidth, frameHeight;
	_renderer->Instance();
	_renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	*vec2 = _renderer->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	rect.x = 4 * frameWidth;
	rect.y = 3 * frameHeight;
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
	pNodeI = pNodeI->next_sibling();
	pNodeI = pNodeI->next_sibling();
	pNodeI = pNodeI->next_sibling();
	rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute();
	numX = pAttr->value();
	pAttr = pAttr->next_attribute();
	numY = pAttr->value();
	x = std::stoi(numX) - 1;
	y = std::stoi(numY) - 1;
	pos.x = x * TILES_PIXEL;
	pos.y = y * TILES_PIXEL;
}
