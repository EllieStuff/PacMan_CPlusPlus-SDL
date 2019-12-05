#include "Map.h"
char InterpretateXML(std::string s)
{
	if (s == "Wall")
	{
		return 'X';
	}
	else
	{
		return 'Y';
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
void Map::Create(Renderer *_renderer)
{
	Vector2 *vec2 = new Vector2(0,0);
	SDL_Rect playerRect, playerPos;
	int textWidth, textHeight, frameWidth, frameHeight;
	_renderer->Instance();
	_renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	_renderer->GetTextureSize("PacmanSheet");
	*vec2 = _renderer->GetTextureSize("PacmanSheet");
	frameWidth = vec2->x / 8;
	frameHeight = vec2->y / 8;
	playerPos.x = playerPos.y = 0;
	playerRect.x = 4;
	playerRect.y = 6;
	playerPos.h = playerRect.h = frameHeight;
	playerPos.w = playerRect.w = frameWidth;
	int frameTimeWallSprite = 0;
	playerRect.x = playerRect.x + frameWidth + 400;
	playerRect.y = playerRect.y + frameHeight + 600;
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
			tiles[x - 1][y - 1] = InterpretateXML(pNodeI->name());
		}
		std::cout << std::endl;
	}
	_renderer->Clear();
	PrintTablero(tiles, _renderer, playerRect, playerPos);
	_renderer->Render();
}
