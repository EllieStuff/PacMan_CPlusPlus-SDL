#include "Map.h"

Objects* Map::InterpretateXML(std::string s, Rect &rect, Rect &pos)
{
	Objects* object = new Objects;
	if (s == "Wall")
	{
		object->tile = MapTiles::WALL;
		object->rect = rect;
		object->rectPos = pos;
		return object;
	}
	else if (s == "Power") {

		object->tile = MapTiles::POWER_UP;
		object->rect = rect;
		object->rectPos = pos;
		return object;
	}


	return object;
}

//void Map::InterpretateXML(std::string s, Rect &newPos, Rect &player, Rect &inky, Rect &blinky, Rect &clyde)
//{
//	if (s == "Player") {
//		player = newPos;
//
//	}
//	else if (s == "Blinky") {
//		blinky = newPos;
//
//	}
//	else if (s == "Inky") {
//		inky = newPos;
//
//	}
//	else if (s == "Clyke") {
//		clyde = newPos;
//
//	}
//}

void InitCharacter(const Rect &newPos, Rect &pos) {
	pos = newPos;

}

//void InitFruit(const Rect &pos, std::vector<std::vector<Objects*>> &o) {
//	o[pos.x][pos.y]->tile = MapTiles::EMPTY_FRUIT;
//
//}

Rect SetXMLPos(rapidxml::xml_attribute<> *pAttr) {
	int x = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
	pAttr = pAttr->next_attribute();
	int y = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
	Rect tmpRect(x, y, TILES_PIXEL, TILES_PIXEL);

	return tmpRect;
}


void Map::InitRemainingTiles(std::vector<std::vector<Objects*>> &_objects, int &_frameWidth, int &_frameHeight)
{
	Rect tmpRect;
	Rect tmpPos;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_objects[i][j]->tile == MapTiles::POINTS)
			{
				maxScore++;
				tmpRect = { 5 * _frameWidth, 6 * _frameHeight, _frameWidth, _frameHeight };
				_objects[i][j]->rect = tmpRect;
				tmpPos = { (i * TILES_PIXEL) , (j * TILES_PIXEL) , TILES_PIXEL , TILES_PIXEL };
				_objects[i][j]->rectPos = tmpPos;
			}
			else if (_objects[i][j]->tile == MapTiles::POWER_UP)
				maxScore += POWER_UP_EXTRA_SCORE;
		}
	}
}

void Map::Create(std::vector<std::vector<Objects*>> &_objects, Rect &player, Rect &inky, Rect &blinky, Rect &clyde)
{

	Vector2 *vec2 = new Vector2(0,0);
	Rect objectRect, objectPos;
	int  frameWidth, frameHeight;
	//Renderer::Instance()->Instance();
	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	*vec2 = Renderer::Instance()->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	objectPos.x = objectPos.y = 0;
	objectRect.x = 4 * frameWidth;
	objectRect.y = 6 * frameHeight;
	objectPos.h = TILES_PIXEL;
	objectRect.h = frameHeight ;
	objectPos.w = TILES_PIXEL;
	objectRect.w = frameWidth ;
	
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
	//for (rapidxml::xml_node<> *pNode = pRoot->first_node("Positions"); pNode; pNode = pNode->next_sibling()) {
	//	for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
	//	{
	//		rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute();
	//		if (pNodeI->name() != "PowerUps") {
	//			x = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
	//			pAttr = pAttr->next_attribute();
	//			y = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
	//			Rect tmpRect(x, y, TILES_PIXEL, TILES_PIXEL);
	//			InterpretateXML(pNodeI->name(), tmpRect, player, inky, blinky, clyde);
	//			std::cout << pNodeI->name() << " coordinates: (" << tmpRect.x << ", " << tmpRect.y << ")\n";
	//		}
	//		//Prq collons llegeix el "PowerUps" si l'estic dient que passi d'ell!!??

	//	}

	//}

	rapidxml::xml_node<> *pNode = pRoot->first_node("Positions");
	pNode = pNode->first_node();
	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
	//Player
	InitCharacter(SetXMLPos(pAttr), player);
	//Fruit
	//InitFruit(SetXMLPos(pAttr), _objects);
	pNode = pNode->next_sibling();
	pAttr = pNode->first_attribute();
	//Blinky
	InitCharacter(SetXMLPos(pAttr), blinky);
	pNode = pNode->next_sibling();
	pAttr = pNode->first_attribute();
	//Inky
	InitCharacter(SetXMLPos(pAttr), inky);
	pNode = pNode->next_sibling();
	pAttr = pNode->first_attribute();
	//Clyde
	InitCharacter(SetXMLPos(pAttr), clyde);

	//Empezamos PowerUps
	pNode = pNode->next_sibling();
	objectRect.x = 6 * frameWidth;
	objectRect.y = 6 * frameHeight;
	for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
	{
		pAttr = pNodeI->first_attribute();
		x = std::stoi(pAttr->value()) - 1;
		pAttr = pAttr->next_attribute();
		y = std::stoi(pAttr->value()) - 1;
		objectPos.x = x * TILES_PIXEL;
		objectPos.y = y * TILES_PIXEL;
		_objects[x][y] = (InterpretateXML(pNodeI->name(), objectRect, objectPos));
	}
	
	//Acabamos PowerUps, empezamos Map
	objectRect.x = 4 * frameWidth;
	objectRect.y = 6 * frameHeight;
	for (pNode = pRoot->first_node("Map")->first_node(); pNode; pNode = pNode->next_sibling())
	{
		rapidxml::xml_attribute<> *pAttrI = pNode->first_attribute();
		x = std::stoi(pAttrI->value()) - 1;
		pAttrI = pAttrI->next_attribute();
		y = std::stoi(pAttrI->value()) - 1;
		objectPos.x = x * TILES_PIXEL;
		objectPos.y = y * TILES_PIXEL;
		_objects[x][y] = (InterpretateXML(pNode->name(), objectRect, objectPos));
	}
	InitRemainingTiles(_objects, frameWidth, frameHeight);
}
void Map::Reinit(std::vector<std::vector<Objects*>>&o)
{
	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (o[i][j]->tile == MapTiles::EMPTY)
			{
				o[i][j]->tile = MapTiles::POINTS;
				o[i][j]->rect.w = frameWidth;
				o[i][j]->rect.h = frameHeight;

			}
			else if (o[i][j]->tile == MapTiles::EMPTY_P_UP)
			{
				o[i][j]->tile = MapTiles::POWER_UP;
				o[i][j]->rect.w = frameWidth;
				o[i][j]->rect.h = frameHeight;

			}
		}
	}

}

void Map::Draw(std::vector<std::vector<Objects*>> &_objects)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			(Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(_objects[i][j]->rect), Utils::RectToSDL_Rect(_objects[i][j]->rectPos)));
		}
	}
}

void Objects::Draw()
{
}

