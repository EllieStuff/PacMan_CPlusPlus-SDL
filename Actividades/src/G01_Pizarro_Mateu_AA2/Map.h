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

	//Functions
	Objects* InterpretateXML(std::string, Rect&, Rect &);
	void InterpretateXML(std::string, Rect&, Rect &, Rect &, Rect &, Rect &);
	void Create(std::vector<std::vector<Objects*>> &, Rect &player, Rect &inky, Rect &blinky, Rect &clyde);
	void InitRemainingTiles(std::vector<std::vector<Objects*>> &, int &, int &);
	void Reinit(std::vector<std::vector<Objects*>> &);
	void Draw(std::vector<std::vector<Objects*>> &);
};