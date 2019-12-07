#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "Types.h"

namespace Utils {
	bool SquareCollidingMouse(Vector2 mouse, Rect square);

	bool OnSquareCollision(const Rect &, const Rect &);

	Rect SDLRect_Rect(SDL_Rect rect);

	SDL_Rect RectToSDL_Rect(Rect rect);

	void Resize(char *text, int size);

	char* int_char(const int &num);
}