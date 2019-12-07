#pragma once
#include <iostream>
#include "Character.h"
#include "Map.h"

class Player : public Character
{
private:
	bool hasPowerUp = false;
	int livesLeft = 3;

public:
	//Direction dir;
	int score = 0;
	int fruits = 0;

	//METHODS
	Player();
	void Move(std::vector<bool> keys);
	bool HitsWall(Direction, std::vector<std::vector<Objects*>>);
	//bool Hit(Map);
	bool GetHasPowerUp();
	void ReinitPos();
	void Reinit();
	//void Update(Map);
	void Draw(Renderer*);
	void LecturaXMLPlayer(Renderer *);
};