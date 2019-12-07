#pragma once
#include <iostream>
#include "Enemies.h"

class Clyde : public Enemies
{
	void Move(Direction, Map);
	void LecturaXMLEnemy();
};