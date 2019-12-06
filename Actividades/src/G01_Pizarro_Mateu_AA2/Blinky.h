#pragma once
#include <iostream>
#include "Enemies.h"

class Blinky : Enemies
{
	void Move(Direction, std::vector<std::vector<Objects*>>);

};