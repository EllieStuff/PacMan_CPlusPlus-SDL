#pragma once
#include <iostream>
#include "Enemies.h"

class Blinky : public Enemies
{
private:
	static Blinky *blinky;

public:
	//Constructor
	Blinky();
	//Singleton
	static Blinky *Instance() {
		if (blinky == nullptr) blinky = new Blinky;

		return blinky;
	}
	//Functions
	void Move(Direction, std::vector<std::vector<Objects*>>);
	//void LecturaXMLEnemy();
};