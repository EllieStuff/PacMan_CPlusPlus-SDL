#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Map.h"

class Character {
private:
	Vector2 initialPos;

protected:
	Rect pos;
	Rect rect;
	//char overlapedSquare;

public:

	virtual void Move() = 0;

	virtual bool HitsWall(std::vector<std::vector<Objects*>>) = 0;

	virtual bool OnEdge() = 0;

	void ReinitPos();

	virtual void Reinit() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

};