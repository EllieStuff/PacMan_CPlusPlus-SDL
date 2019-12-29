#pragma once
#include <iostream>
#include <time.h>
#include "Character.h"
#include "Map.h"
#include "Fruit.h"
#include "Enemies.h"
#include "Inky.h"
#include "Clyde.h"
#include "Blinky.h"

class Player : public Character
{
private: 
	Direction goingToMove = Direction::NONE;
	void FinishPowerUp(Clyde *, Inky*, Blinky *);
	int maxScore = 0;

public:
	Direction dir = Direction::NONE;
	time_t powerUpEnd;
	int score = 0;
	int fruits = 0;
	bool hasPowerUp = false;
	int livesLeft = 3;
	bool dead = false;
	int frameTimeSprite = 0;
	bool hasHitEnemy = false;
	//Constructor
	Player();
	//Functions
	bool OnEdge();
	void Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Clyde *, Inky *, Blinky *, Fruit &);
	bool Hits(std::vector<std::vector<Objects*>> &, Clyde *, Inky *, Blinky *, Fruit &);
	void Reinit(const int &);
	int GetMaxScore();

};