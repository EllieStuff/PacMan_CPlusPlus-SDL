#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
//#include "Map.h"

class Character {
protected:
	Vector2 initialPos;
	Vector2 lastPos; 
public:
	Rect pos;
	Rect rect;
	//Constructor
	Character();
	//Functions
	void SetInitPos(int &_x, int &_y);
	virtual void Move();
	virtual bool OnEdge();
	void ReinitPos();
	virtual void Reinit();
	virtual void Update();
	virtual void Draw();
};