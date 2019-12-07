#pragma once
#include <iostream>
#include "Character.h"
#include "Map.h"
#include "Enemies.h"

class Player : public Character
{
public:
	Direction dir = Direction::NONE;
	int score = 0;
	int fruits = 0;
	bool hasPowerUp = false;
	int livesLeft = 3;

	//METHODS
	Player();
	bool OnEdge();
	void Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Rect &_clydePos, Rect &_inkyPos);
	bool Hits(std::vector<std::vector<Objects*>> &, Rect&, Rect&);
	bool GetHasPowerUp();
	void ReinitPos();
	void Reinit();
	//void Update(Map);
	void Draw(Renderer*);
	void LecturaXMLPlayer(Renderer *);
};