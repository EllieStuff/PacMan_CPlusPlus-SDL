#pragma once
#include <vector>
#include <iostream>
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Renderer.h"
#include <string>
#include <sstream>

#include "../XML/rapidxml.hpp"
#include "../XML/rapidxml_iterators.hpp"
#include "../XML/rapidxml_print.hpp"
#include "../XML/rapidxml_utils.hpp"


#include "Character.h"
#include "Player.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Enemies.h"

//class Objects {
//public:
//	MapTiles tile;
//	Rect rect, rectPos;
//	//Functions
//	void Draw();
//};

class Map {
public:
	int maxScore = 0;

	//Functions
	Objects* InterpretateXML(std::string, Rect&, Rect &);
	void InterpretateXML(std::string, Rect&);
	void Create(std::vector<std::vector<Objects*>> &);
	void InitRemainingTiles(std::vector<std::vector<Objects*>> &, int &, int &);
	void Reinit(std::vector<std::vector<Objects*>> &);
	void Draw(std::vector<std::vector<Objects*>> &);
};