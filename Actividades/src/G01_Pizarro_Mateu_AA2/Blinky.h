#pragma once
#include <iostream>
#include "Enemies.h"

class Blinky : public Enemies
{

	void Move(Direction, std::vector<std::vector<Objects*>>);
	void LecturaXMLEnemy();
};