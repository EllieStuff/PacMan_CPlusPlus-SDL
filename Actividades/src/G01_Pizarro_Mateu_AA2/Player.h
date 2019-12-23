#pragma once
#include <iostream>
//#include "Character.h"
//#include "Map.h"
//#include "Enemies.h"
#include "Inky.h"
#include "Clyde.h"

class Player : public Character
{
private:
	Direction goingToMove = Direction::NONE;
	static Player *player;

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
	//Singleton
	static Player *Instance() {
		if (player == nullptr) player = new Player;

		return player;
	}
	//Functions
	bool OnEdge();
	void Move(std::vector<bool> keys, std::vector<std::vector<Objects*>> &o);
	bool Hits(std::vector<std::vector<Objects*>> &);
	bool GetHasPowerUp();
	void Reinit();
	void Draw();
	void SetScore(int);
	//void LecturaXMLPlayer();
};