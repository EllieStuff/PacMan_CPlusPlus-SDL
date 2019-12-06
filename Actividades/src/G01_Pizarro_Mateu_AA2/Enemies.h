#pragma once
#include "Character.h"

class Enemies : public Character
{
private:
	EnemyType type;

public:
	virtual void Move(Direction, std::vector<std::vector<Objects*>>) = 0;
	bool HitsWall(Direction playerDir, std::vector<std::vector<Objects*>>);
	bool OnEdge();
	void Reinit();
	void Update(Direction, Map);
	void Draw();

};