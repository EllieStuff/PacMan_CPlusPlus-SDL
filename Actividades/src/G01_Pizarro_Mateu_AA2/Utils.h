#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "Types.h"
#include "Constants.h"

namespace Utils {
	//Functions
	int PointsDistance(const Rect &point1, const Rect &point2);
	bool SquareCollidingMouse(Vector2 mouse, Rect square);
	bool OnSquareCollision(const Rect &, const Rect &);
	Rect SDLRect_Rect(SDL_Rect rect);
	SDL_Rect RectToSDL_Rect(Rect rect);
	Vector2 Rect_Vec2(Rect rect);
	std::string AddZerosInFrontOfStr(int num, int maxZeros);
	void Resize(char *text, int size);
	char* int_char(const int &num);
}