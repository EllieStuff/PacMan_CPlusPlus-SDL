#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Map.h"

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
	virtual void Move();
	virtual bool OnEdge();
	virtual void Reinit();
	virtual void Update();
	
	void ReinitPos();
	void SetInitPos();
	void Draw();

};