#pragma once
#include <vector>
#include <iostream>
#include "Constants.h"
#include "Types.h"
#include "Renderer.h"
#include <string>
#include <sstream>

#include "../XML/rapidxml.hpp"
#include "../XML/rapidxml_iterators.hpp"
#include "../XML/rapidxml_print.hpp"
#include "../XML/rapidxml_utils.hpp"

#include "Utils.h"
#include "Character.h"
#include "Player.h"
#include "Inky.h"
#include "Clyde.h"
#include "Blinky.h"

class Objects {
public:
	MapTiles tile;
	Rect rect, rectPos;
	//Functions
	void Draw();
};



class Map {
public:
	int maxScore = 0;
	std::vector<std::vector<Objects*>> objects[MAP_WIDTH][MAP_HEIGHT];
	//Functions
	Objects* SaveWallsXML(std::string, SDL_Rect&, SDL_Rect &);
	void Create(Renderer *, std::vector<std::vector<Objects*>> &);
	void InitRemainingTiles(std::vector<std::vector<Objects*>> &, int &, int &);
	void Reinit(Renderer *, std::vector<std::vector<Objects*>> &);
	void Draw(Renderer*, std::vector<std::vector<Objects*>> &);
};