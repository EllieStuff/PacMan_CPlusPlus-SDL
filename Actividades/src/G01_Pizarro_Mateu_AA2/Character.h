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
	//Character();
	virtual void Move();
	//virtual bool HitsWall(Direction, std::vector<std::vector<Objects*>>);

	virtual bool OnEdge();

	void ReinitPos();

	virtual void Reinit();

	virtual void Update();

	virtual void Draw(Renderer*);

};