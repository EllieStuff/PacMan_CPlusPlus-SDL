#include "Map.h"
Rect SDLRect_Rect(SDL_Rect rect) {
	Rect r(rect.x, rect.y, rect.w, rect.h);

	return r;
}
SDL_Rect RectToSDL_Rect(Rect rect)
{
	SDL_Rect r;
	r.x = rect.x; r.y = rect.y;
	r.w = rect.w; r.h = rect.h;
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
Objects* Map::InterpretateXML(std::string s, SDL_Rect &_objectRect, SDL_Rect &_objectPos, SDL_Rect &_playerRect,)
{
	Objects* object = new Objects;
	if (s == "Wall")
	{
		object->tile = MapTiles::WALL;
		object->rect = SDLRect_Rect(_objectRect);
		object->rectPos = SDLRect_Rect(_objectPos);
		//object = reinterpret_cast<Wall*>(object);
		return object;
	}
	if (s == "Player")
	{
		 
	}
	if (s == "Inky")
	{

	}
	if (s == "Clyke")
	{

	}
	return object;
}
void PrintTablero(std::vector<std::vector<Objects*>> _o, Renderer *_renderer)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			(_renderer->PushSprite("PacmanSheet", RectToSDL_Rect(_o[i][j]->rect), RectToSDL_Rect(_o[i][j]->rectPos)));
		}
		std::cout << std::endl;
	}
}

void InitTablero(std::vector<std::vector<Objects*>> _objects, int &_frameWidth, int &_frameHeight)
{
	Rect r (5 * _frameWidth,6 * _frameHeight, _frameWidth, _frameHeight);
	Rect r2;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (_objects[i][j]->tile == MapTiles::POINTS)
			{
				_objects[i][j]->rect = r;
				r2 = {(i * TILES_PIXEL) , (j * TILES_PIXEL) , TILES_PIXEL , TILES_PIXEL };
				_objects[i][j]->rectPos = r2;
			}
		}
	}
}

void Map::Create(Renderer *_renderer, std::vector<std::vector<Objects*>> _objects)
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
	objectPos.x = objectPos.y = 0;
	objectRect.x = 4 * frameWidth;
	objectRect.y = 6 * frameHeight;
	objectPos.h = TILES_PIXEL;
	objectRect.h = frameHeight ;
	objectPos.w = TILES_PIXEL;
	objectRect.w = frameWidth ;
#pragma endregion
	
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
			x = std::stoi(numX) - 1;
			y = std::stoi(numY) - 1;
			objectPos.x = x  * TILES_PIXEL;
			objectPos.y = y  * TILES_PIXEL;
			//if (pNodeI->name() == "Wall")
			_objects[x][y] = (InterpretateXML(pNodeI->name(), objectRect, objectPos));
		}
		std::cout << std::endl;
	}
	InitTablero(_objects, frameWidth, frameHeight);
	_renderer->Clear();
	PrintTablero(_objects, _renderer);
	_renderer->Render();
}

void Map::Draw(Renderer* _renderer, std::vector<std::vector<Objects*>> _objects)
{
	
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

