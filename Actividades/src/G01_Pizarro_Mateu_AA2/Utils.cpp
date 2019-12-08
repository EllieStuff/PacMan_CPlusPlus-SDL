#include "Utils.h"


bool PointCollidingSquare(Rect point, Rect square) {

	return point.x > square.x && point.x < square.x + square.w
		&& point.y > square.y && point.y < square.y + square.h;
}

int Utils::PointsDistance(const Rect &point1, const Rect &point2) {
	

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

bool Utils::OnSquareCollision(const Rect &avatar, const Rect &square) {		//Recordar canviar nom
	Rect point1(avatar.x + avatar.w / 2, avatar.y + avatar.h, NULL, NULL);
	Rect point2(square.x + square.w / 2, square.y + square.h, NULL, NULL);

	return PointsDistance(avatar, square) < TILES_PIXEL;
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

Vector2 Utils::Rect_Vec2(Rect rect)
{
	Vector2 v(rect.x, rect.y);

	return v;
}

std::string Utils::AddZerosInFrontOfStr(int num, int maxZeros) {
	if (num <= 0) return "0000";

	std::string numStr = std::to_string(num);
	std::string result = "";
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}

	for (int i = count; i < maxZeros; i++) {
		result += "0";
	}

	result += numStr;

	return result;
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