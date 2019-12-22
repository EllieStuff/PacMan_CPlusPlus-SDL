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
	bool hasHitEnemy = false;
	//Constructor
	Player();
	//Functions
	bool OnEdge();
	void Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o, Clyde *, Inky *);
	bool Hits(std::vector<std::vector<Objects*>> &, Clyde *, Inky *);
	bool GetHasPowerUp();
	void Reinit();
	void Draw();
	void LecturaXMLPlayer();
};