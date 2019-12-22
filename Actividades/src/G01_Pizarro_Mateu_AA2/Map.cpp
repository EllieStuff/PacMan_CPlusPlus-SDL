#include "Map.h"

Objects* Map::SaveWallsXML(std::string s, SDL_Rect &_objectRect, SDL_Rect &_objectPos)
{
	Objects* object = new Objects;
	if (s == "Wall")
	{
		object->tile = MapTiles::WALL;
		object->rect = Utils::SDLRect_Rect(_objectRect);
		object->rectPos = Utils::SDLRect_Rect(_objectPos);
		return object;
	}
	if (s == "Power")
	{
		object->tile = MapTiles::POWER_UP;
		object->rect = Utils::SDLRect_Rect(_objectRect);
		object->rectPos = Utils::SDLRect_Rect(_objectPos);
		return object;
	}
	return object;
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
				tmpPos = {(i * TILES_PIXEL) , (j * TILES_PIXEL) , TILES_PIXEL , TILES_PIXEL };
				_objects[i][j]->rectPos = tmpPos;
			}
		}
	}
}

void Map::Create(Renderer *_renderer, std::vector<std::vector<Objects*>> &_objects)
{

	Vector2 *vec2 = new Vector2(0,0);
	SDL_Rect objectRect, objectPos;
	int  frameWidth, frameHeight;
	_renderer->Instance();
	_renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	*vec2 = _renderer->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	objectPos.x = objectPos.y = 0;
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
	rapidxml::xml_node<> *pNode = pRoot->first_node("Positions");
	//Entramos en hijos Positions
	rapidxml::xml_node<> *pNodeI = pNode->first_node();
	rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute();
	Player::Instance()->pos.x = std::stoi(pAttr->value()) - 1;
	pAttr = pAttr->next_attribute();
	Player::Instance()->pos.y = std::stoi(pAttr->value()) - 1;

	//Acabamos player, empezamos blinky
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	Blinky::Instance()->pos.x = std::stoi(pAttr->value()) - 1;
	pAttr = pAttr->next_attribute();
	Blinky::Instance()->pos.y = std::stoi(pAttr->value()) - 1;

	//Acabamos blinky, empezamos inky
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	Inky::Instance()->pos.x = std::stoi(pAttr->value()) - 1;
	pAttr = pAttr->next_attribute();
	Inky::Instance()->pos.y = std::stoi(pAttr->value()) - 1;

	//Acabamos inky, empezamos Clyde
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	Clyde::Instance()->pos.x = std::stoi(pAttr->value()) - 1;
	pAttr = pAttr->next_attribute();
	Clyde::Instance()->pos.y = std::stoi(pAttr->value()) - 1;

	//Empezamos PowerUps
	pNodeI = pNodeI->next_sibling();
	objectRect.x = 6 * frameWidth;
	objectRect.y = 6 * frameHeight;
	for (rapidxml::xml_node<> *pNodeII = pNodeI->first_node(); pNodeII; pNodeII = pNodeII->next_sibling())
	{
		rapidxml::xml_attribute<> *pAttrI = pNodeII->first_attribute();
		objectPos.x = (std::stoi(pAttrI->value()) - 1) * TILES_PIXEL;
		pAttrI = pAttrI->next_attribute();
		objectPos.y = (std::stoi(pAttrI->value()) - 1) * TILES_PIXEL;
		_objects[x][y] = (SaveWallsXML(pNodeII->name(), objectRect, objectPos));
	}

	//Acabamos PowerUps, empezamos Map
	pNode = pNode->next_sibling();
	objectRect.x = 4 * frameWidth;
	objectRect.y = 6 * frameHeight;
	for (pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
	{
		pAttr = pNodeI->first_attribute();
		objectPos.x = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
		pAttr = pAttr->next_attribute();
		objectPos.y = (std::stoi(pAttr->value()) - 1) * TILES_PIXEL;
		_objects[x][y] = (SaveWallsXML(pNodeI->name(), objectRect, objectPos));
	}
	InitRemainingTiles(_objects, frameWidth, frameHeight);
}

void Map::Reinit(Renderer *renderer, std::vector<std::vector<Objects*>>&o)
{
	renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
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
		}
	}

}

void Map::Draw(Renderer* _renderer, std::vector<std::vector<Objects*>> &_objects)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			(_renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(_objects[i][j]->rect), Utils::RectToSDL_Rect(_objects[i][j]->rectPos)));
		}
	}
}

void Objects::Draw()
{
}

