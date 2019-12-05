#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>

namespace Utils {
	//bool SquareCollidingMouse(Vector2 mouse, Rect square) {

	//	return mouse.x > square.x && mouse.x < square.x + square.w
	//		&& mouse.y > square.y && mouse.y < square.y + square.h;

	//}

	//Rect SDLRect_Rect(SDL_Rect rect) {
	//	Rect r(rect.x, rect.y, rect.w, rect.h);

	//	return r;
	//}

	//void Resize(char *text, int size) {
	//	char *newText = new char[size];
	//	for (int i = 0; i < size && text[i] != '\0'; i++)
	//		newText[i] = text[i];

	//	delete[] text;
	//	text = newText;

	//}

	//char* int_char(const int &num) {
	//	char *text = new char[1];
	//	if (num < 10) {
	//		text[0] = num + 48;
	//		//Arreglo provisional
	//		for (int i = 1; i < 6; i++) text[i] = ' ';

	//		return text;
	//	}
	//	int numCopy = num;
	//	int size = 1;
	//	while (numCopy >= 10) {
	//		size++;
	//		numCopy /= 10;
	//	}
	//	Resize(text, size);
	//	text[0] = numCopy + 48;

	//	for (int i = 1; i < size; i++) {
	//		int lastNum = numCopy;
	//		numCopy = num;
	//		for (int j = 0; j < size - i; j++) lastNum *= 10;
	//		numCopy -= lastNum;
	//		while (numCopy >= 10) numCopy /= 10;

	//		text[i] = numCopy + 48;

	//	}
	//	//Prq collons surten aquelles Ý si l'array només té dos espais??!!
	//	//Arreglo provisional
	//	for (int i = 2; i < 6; i++) text[i] = ' ';

	//	return text;

	//}
	
}