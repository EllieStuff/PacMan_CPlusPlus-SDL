#pragma once
#include <iostream>
#include "Character.h"
#include "Map.h"
#include "Enemies.h"
#include "Inky.h"
#include "Clyde.h"

class Player : public Character
{
private: 
	Direction goingToMove = Direction::NONE;
public:
	Direction dir = Direction::NONE;
	int score = 0;
	int fruits = 0;
	bool hasPowerUp = false;
	int livesLeft = 3;
	bool dead = false;
	int frameTimeSprite = 0;
	bool hasHittedEnemy = false;

	//METHODS
	Player();
	bool OnEdge();
	void Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Clyde *, Inky *);
	bool Hits(std::vector<std::vector<Objects*>> &, Clyde *, Inky *);
	//bool HitsEnemy(Rect _clydePos, Rect _inkyPos);
	bool GetHasPowerUp();
	//void ReinitPos();
	void Reinit(Renderer *);
	//void Update(Map);
	void Draw(Renderer*);
	void LecturaXMLPlayer(Renderer *);
};