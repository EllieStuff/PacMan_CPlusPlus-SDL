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
class Objects {
public:
	MapTiles tile;
	Rect rect, rectPos;
	void Equalize(Objects*);
	virtual void InteractWithPlayer();

	virtual void TouchingPlayer();

	void Draw();

	
	
private:

};

struct Wall : Objects {
	void InteractWithPlayer();
	void TouchingPlayer();

};

struct Points : Objects {
	void InteractWithPlayer();
	void TouchingPlayer();

};

struct Fruit : Objects {
	void InteractWithPlayer();
	void TouchingPlayer();

};

struct PowerUp : Objects {
	void InteractWithPlayer();
	void TouchingPlayer();

};


class Map {
public:
	char tiles[MAP_WIDTH][MAP_HEIGHT];
	std::vector<std::vector<Objects*>> objects[MAP_WIDTH][MAP_HEIGHT];
	Objects* InterpretateXML(std::string, SDL_Rect&, SDL_Rect &);

	void Create(Renderer *, std::vector<std::vector<Objects*>>);

	void Refresh();

	void Draw();

	//Map(std::vector<std::vector<Objects*>> _objects)
	//{
	//	_objects[1][1].e
	//	// Displaying the 2D vector 
	//	for (int i = 0; i < _objects.size(); i++) {
	//		for (int j = 0; j < _objects[i].size(); j++)
	//			//std::cout << _objects[i][j]. << " ";
	//		//std::cout << std::endl;
	//	}
	//}
private:

};