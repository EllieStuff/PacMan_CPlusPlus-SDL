#pragma once
#include "Character.h"

class Enemies : Character
{
private:
	Vector2 initialPos;
	Rect rect;
	EnemyType type;
	char overlapedSquare;

public:
	virtual void Move(Direction, Map);
	bool Hit(Map);
	void ReinitPos();
	void Reinit();
	void Update(Direction, Map);
	void Draw();

};