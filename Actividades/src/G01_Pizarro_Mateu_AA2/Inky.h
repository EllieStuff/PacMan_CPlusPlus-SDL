#pragma once
#include <iostream>
#include "Enemies.h"

class Inky : public Enemies
{
private:
	static Inky *inky;
public:
	//Constructor
	Inky();
	//Functions
	static Inky *Instance()
	{
		if (inky = nullptr) { inky = new Inky; }
		return inky;
	}
	void Move(Direction, std::vector<std::vector<Objects*>>);
	void LecturaXMLEnemy(Renderer*);
};