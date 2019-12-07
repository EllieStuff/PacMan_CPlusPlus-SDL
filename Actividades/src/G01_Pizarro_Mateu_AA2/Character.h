#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Map.h"

class Character {
protected:
	Vector2 initialPos;
	Vector2 lastPos; 
	Rect rect;
	//char overlapedSquare;

public:
	Rect pos;

	Character();
	virtual void Move();
	//virtual bool HitsWall(Direction, std::vector<std::vector<Objects*>>);

	virtual bool OnEdge();

	void ReinitPos();

	virtual void Reinit();

	virtual void Update();

	virtual void Draw(Renderer*);

};