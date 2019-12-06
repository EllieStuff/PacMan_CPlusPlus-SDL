#include "Map.h"
Rect SDLRect_Rect(SDL_Rect rect) {
	Rect r(rect.x, rect.y, rect.w, rect.h);

	return r;
}
void Objects::Equalize(Objects *o)
{
	tile = o->tile;
	rect.x = o->rect.x;
	rect.y = o->rect.y;
	rect.w = o->rect.w;
	rect.h = o->rect.h;
	rectPos.x = o->rectPos.x;
	rectPos.y = o->rectPos.y;
	rectPos.w = o->rectPos.w;
	rectPos.h = o->rectPos.h;
}
Objects* Map::InterpretateXML(std::string s, SDL_Rect &_objectRect, SDL_Rect &_objectPos)
{
	Objects* object = new Objects;
	if (s == "Wall")
	{
		object->tile = MapTiles::WALL;
		object->rect = SDLRect_Rect(_objectRect);
		object->rectPos = SDLRect_Rect(_objectPos);
		return object;
	}
}
void PrintTablero(char c[][20], Renderer *_renderer, SDL_Rect &playerRect, SDL_Rect &playerPos)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			std::cout << c[j][i];
			(_renderer->PushSprite("PacmanSheet", playerRect, playerPos));
		}
		std::cout << std::endl;
	}
}
void InitTablero(char c[][20])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			c[i][j] = ' ';
		}
	}
}

//int frameWidth, frameHeight;
void Map::Create(Renderer *_renderer)
{
#pragma region RENDERER
	Vector2 *vec2 = new Vector2(0,0);
	SDL_Rect objectRect, objectPos;
	int textWidth, textHeight, frameWidth, frameHeight;
	_renderer->Instance();
	_renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	*vec2 = _renderer->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	objectPos.x = objectPos.y = 50;
	objectRect.x = 4 * frameWidth;
	objectRect.y = 6 * frameHeight;
	objectPos.h = frameHeight / 2;
	objectRect.h = frameHeight ;
	objectPos.w = frameHeight / 2;
	objectRect.w = frameWidth ;
	//int frameTimeWallSprite = 0;
#pragma endregion
	InitTablero(tiles);
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
			x = std::stoi(numX);
			y = std::stoi(numY);
			objects[2][2] = (InterpretateXML(pNodeI->name(),objectRect, objectPos));
		}
		std::cout << std::endl;
	}
	_renderer->Clear();
	PrintTablero(tiles, _renderer, objectRect, objectPos);
	_renderer->Render();
}

void Objects::InteractWithPlayer()
{

}

void Objects::TouchingPlayer()
{

}

void Objects::Draw()
{

}

