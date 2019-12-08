#pragma once
#include <iostream>
#include "Enemies.h"

class Inky : public Enemies
{
public:
	Inky();

	void Move(Direction, std::vector<std::vector<Objects*>>);
	
	void LecturaXMLEnemy(Renderer*);
};