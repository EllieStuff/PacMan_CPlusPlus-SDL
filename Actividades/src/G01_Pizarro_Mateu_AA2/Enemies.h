#pragma once
#include "Character.h"

class Enemies : public Character
{
protected:
	Direction dir = Direction::NONE;

public:
	int extraScore;

	Enemies();
	virtual void Move(Direction, std::vector<std::vector<Objects*>>);
	bool HitsWall(Direction, std::vector<std::vector<Objects*>>);
	bool OnEdge();
	void Reinit();
	void Update(Direction, Map);
	void Draw(Renderer*);
	virtual void LecturaXMLEnemy(Renderer*);
};