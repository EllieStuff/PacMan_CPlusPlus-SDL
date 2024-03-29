#pragma once
#include <string>
#include "Renderer.h"
#include"Utils.h"
#include "Constants.h"
#include"Types.h"
#include "Player.h"


class HUD {
private:
	enum TypeOfRect { RECT = 0, SPRITE, TEXT, COUNT };
	Color textColor;
public:
	Font font;
	Rect bgRect;
	Rect bgPos;
	Rect score;
	Text scoreText;
	Rect lives[3][static_cast<int>(COUNT)];
	Rect cherry[static_cast<int>(COUNT)];
	Text cherText;
	Rect sb[static_cast<int>(COUNT)];
	Text sbText;
	Rect orange[static_cast<int>(COUNT)];
	Text oranText;
	//Constructor
	HUD(Player *);
	//Functions
	void Update(Player *);
	void Draw(Player *);

};