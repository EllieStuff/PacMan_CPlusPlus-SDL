#include "Inky.h"

void Inky::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	Direction enemyDir = playerDir;
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

void Inky::LecturaXMLEnemy()
{
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
	rapidxml::xml_node<> *pNode = pRoot->first_node("Inky");
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
	numX = pAttr->value();
	pAttr = pAttr->next_attribute();
	numY = pAttr->value();
	x = std::stoi(numX) - 1;
	y = std::stoi(numY) - 1;
	pos.x = x * TILES_PIXEL;
	pos.y = y * TILES_PIXEL;
}
