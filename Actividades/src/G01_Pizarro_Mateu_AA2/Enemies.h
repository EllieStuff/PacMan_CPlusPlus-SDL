#pragma once
#include "Character.h"

class Enemies : public Character
{
protected:
	Direction dir = Direction::NONE;
public:
	int extraScore;
	//Constructor
	Enemies();
	//Functions
	virtual void Move(Direction, std::vector<std::vector<Objects*>>);
	bool HitsWall(Direction, std::vector<std::vector<Objects*>>);
	bool OnEdge();
	void Reinit();
	void Update(Direction, Map);
	void Draw();
	//virtual void LecturaXMLEnemy();
};