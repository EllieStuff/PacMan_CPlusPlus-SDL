#pragma once
#include <iostream>
#include "Enemies.h"

class Clyde : public Enemies
{
public:
	Clyde() {};
	void Move(Direction, std::vector<std::vector<Objects*>>);
	void LecturaXMLEnemy(Renderer*);
};