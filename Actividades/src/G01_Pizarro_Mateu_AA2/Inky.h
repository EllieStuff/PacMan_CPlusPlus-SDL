#pragma once
#include <iostream>
#include "Enemies.h"

class Inky : public Enemies
{
public:
	//Constructor
	Inky();
	//Functions
	void Move(Direction, std::vector<std::vector<Objects*>>);

};