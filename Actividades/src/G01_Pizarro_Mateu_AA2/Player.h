#pragma once
#include <iostream>
#include "Character.h"

class Player : Character
{
private:
	bool hasPowerUp = false;
	int livesLeft = 3;

public:
	Direction dir;
	int score = 0;
	int fruits = 0;

	//METHODS
	void Move(Map);
	bool Hit(Map);
	bool GetHasPowerUp();
	void ReinitPos();
	void Reinit();
	void Update(Map);
	void Draw();

};