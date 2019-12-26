#pragma once
#include <time.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Renderer.h"
#include "Map.h"

struct Fruit {
private:
	FruitTypes currentType = FruitTypes::EMPTY;
	FruitTypes lastType = FruitTypes::EMPTY;
	const int CHERRY_VALUE = 10;
	const int SB_VALUE = 15;
	const int ORANGE_VALUE = 20;

	void ChangeFruit();

public:
	long long tDif = 0;
	int extraScore = 0;
	Rect rect, pos;
	FruitTypes publicType = FruitTypes::EMPTY;

	Fruit() {};

	void Init(const Rect &_pos);

	void EraseFruit();

	void Instantiate();

	void Draw();

	void Reinit();

};