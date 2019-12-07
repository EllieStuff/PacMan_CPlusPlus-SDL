#pragma once
#include <iostream>
#include "Character.h"
#include "Map.h"
#include "Enemies.h"

class Player : public Character
{
private:
	bool hasPowerUp = false;
	int livesLeft = 3;

public:
	Direction dir;
	int score = 0;
	int fruits = 0;

	//METHODS
	Player();
	bool OnEdge();
	void Move(std::vector<bool> keys);
	bool Hits(Direction, std::vector<std::vector<Objects*>>, Rect&, Rect&);
	bool GetHasPowerUp();
	void ReinitPos();
	void Reinit();
	//void Update(Map);
	void Draw(Renderer*);
	void LecturaXMLPlayer(Renderer *);
};