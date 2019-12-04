#pragma once
#include <vector>
#include "Constants.h"
#include "Types.h"

class Objects {
public:
	MapTiles tile;
	Rect rect;

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

	void Create();

	void Refresh();

	void Draw();

private:

};