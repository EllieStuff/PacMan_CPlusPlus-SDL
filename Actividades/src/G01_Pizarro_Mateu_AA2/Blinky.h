#pragma once
#include <iostream>
#include "Enemies.h"

class Blinky : public Enemies
{
private:
	void AddPos();
	void DecidePos(const Direction &forbiddenDir, std::vector<std::vector<Objects*>>);

public:
	//Constructor
	Blinky();
	//Functions
	void Move(std::vector<std::vector<Objects*>>);

};