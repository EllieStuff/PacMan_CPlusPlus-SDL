#pragma once
#include <string>
#include "Renderer.h"
#include"Utils.h"
#include "Constants.h"
#include"Types.h"


class HUD {
private:
	enum TypeOfRect { RECT = 0, SPRITE, TEXT, COUNT };

public:
	Font font;
	Rect score;
	Text scoreText;
	Rect lives[3][static_cast<int>(COUNT)];
	Rect cherry[static_cast<int>(COUNT)];
	Text cherText;
	Rect sb[static_cast<int>(COUNT)];
	Text sbText;
	Rect orange[static_cast<int>(COUNT)];
	Text oranText;

	//Functions
	HUD(Renderer *renderer);

	void Update();

	void Draw();

};