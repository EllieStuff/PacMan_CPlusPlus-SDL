#pragma once
#include <iostream>
#include "Enemies.h"

class Inky : public Enemies
{
	void Move(Direction, std::vector<std::vector<Objects*>>);

};