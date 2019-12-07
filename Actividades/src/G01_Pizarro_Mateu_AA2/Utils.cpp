#include "Utils.h"

bool Utils::SquareCollidingMouse(Vector2 mouse, Rect square) {

	return mouse.x > square.x && mouse.x < square.x + square.w
		&& mouse.y > square.y && mouse.y < square.y + square.h;

}


bool Utils::OnSquareCollision(const Rect &avatar, const Rect &square) {

	return avatar.x > square.x && avatar.x < square.x + square.w
		&& avatar.y > square.y && avatar.y < square.y + square.h;
}

Rect Utils::SDLRect_Rect(SDL_Rect rect) {
	Rect r(rect.x, rect.y, rect.w, rect.h);

	return r;
}

SDL_Rect Utils::RectToSDL_Rect(Rect rect)
{
	SDL_Rect r;
	r.x = rect.x; r.y = rect.y;
	r.w = rect.w; r.h = rect.h;
	return r;
}

void Utils::Resize(char *text, int size) {
	char *newText = new char[size];
	for (int i = 0; i < size && text[i] != '\0'; i++)
		newText[i] = text[i];

	delete[] text;
	text = newText;

}

char* Utils::int_char(const int &num) {
	char *text = new char[1];
	if (num < 10) {
		text[0] = num + 48;
		//Arreglo provisional
		for (int i = 1; i < 6; i++) text[i] = ' ';

		return text;
	}
	int numCopy = num;
	int size = 1;
	while (numCopy >= 10) {
		size++;
		numCopy /= 10;
	}
	Utils::Resize(text, size);
	text[0] = numCopy + 48;

	for (int i = 1; i < size; i++) {
		int lastNum = numCopy;
		numCopy = num;
		for (int j = 0; j < size - i; j++) lastNum *= 10;
		numCopy -= lastNum;
		while (numCopy >= 10) numCopy /= 10;

		text[i] = numCopy + 48;

	}
	//Prq collons surten aquelles � si l'array nom�s t� dos espais??!!
	//Arreglo provisional
	for (int i = 2; i < 6; i++) text[i] = ' ';

	return text;

}