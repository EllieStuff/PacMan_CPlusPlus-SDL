#pragma once
#include "Character.h"

class Enemies : public Character
{
public:
	Direction dir = Direction::NONE;
	int extraScore;
	bool dying = false;
	//Constructor
	Enemies();
	//Functions
	virtual void Move(Direction, std::vector<std::vector<Objects*>>);
	virtual void Move(std::vector<std::vector<Objects*>>);
	bool HitsWall(Direction, std::vector<std::vector<Objects*>>);
	bool HitsWall(const int &dirN, std::vector<std::vector<Objects*>>);
	bool OnEdge();
	void Reinit();
	void Update(Direction, Map);
	virtual void LecturaXMLEnemy();
};