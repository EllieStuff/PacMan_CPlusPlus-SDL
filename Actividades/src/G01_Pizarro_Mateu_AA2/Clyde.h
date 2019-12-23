#pragma once
#include <iostream>
#include "Enemies.h"

class Clyde : public Enemies
{
private:
	static Clyde *clyde;

public:
	//Constructor
	Clyde();
	//Singleton
	static Clyde *Instance() {
		if (clyde == nullptr) clyde = new Clyde;

		return clyde;
	}
	//Functions
	void Move(Direction, std::vector<std::vector<Objects*>>);
	//void LecturaXMLEnemy();
};