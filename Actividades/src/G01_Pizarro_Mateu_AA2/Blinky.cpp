#include "Blinky.h"

void Blinky::Move(Direction playerDir, std::vector<std::vector<Objects*>> mapObjects)
{
	
}

void Blinky::LecturaXMLEnemy()
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
	rapidxml::xml_node<> *pNode = pRoot->first_node("Blinky");
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
	numX = pAttr->value();
	pAttr = pAttr->next_attribute();
	numY = pAttr->value();
	x = std::stoi(numX) - 1;
	y = std::stoi(numY) - 1;
	pos.x = x * TILES_PIXEL;
	pos.y = y * TILES_PIXEL;
}
