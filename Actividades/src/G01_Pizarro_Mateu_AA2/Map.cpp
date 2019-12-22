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

void Map::Create(std::vector<std::vector<Objects*>> &_objects)
{

	Vector2 *vec2 = new Vector2(0,0);
	SDL_Rect objectRect, objectPos;
	int  frameWidth, frameHeight;
	Renderer::Instance()->Instance();
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
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("Map"); pNode; pNode = pNode->next_sibling())
	{
		std::cout << pNode->name() << ':' << std::endl;
		for (rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(); pAttr; pAttr->next_attribute())
		{
			std::cout << '-' << pAttr->name() << '-' << pAttr->value();
		}
		for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			rapidxml::xml_attribute<> *pAttr = pNodeI->first_attribute();
			numX = pAttr->value();
			pAttr = pAttr->next_attribute();
			numY = pAttr->value();
			x = std::stoi(numX) - 1;
			y = std::stoi(numY) - 1;
			objectPos.x = x  * TILES_PIXEL;
			objectPos.y = y  * TILES_PIXEL;
			_objects[x][y] = (SaveWallsXML(pNodeI->name(), objectRect, objectPos));
		}
		std::cout << std::endl;
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

