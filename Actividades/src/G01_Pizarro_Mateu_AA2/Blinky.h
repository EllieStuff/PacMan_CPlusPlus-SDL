#pragma once
#include <iostream>
#include "Enemies.h"

class Blinky : public Enemies
{
public:
	//Constructor
	Blinky();
	//Functions
	void Move(Direction, std::vector<std::vector<Objects*>>);
	void LecturaXMLEnemy();
};