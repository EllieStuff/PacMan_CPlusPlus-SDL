#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <SDL.h>	

struct Vector2 {
	int x, y;

	Vector2() {};
	Vector2(const int &_x, const int &_y) : x(_x), y(_y) {};
	Vector2(const Vector2 &v) : x(v.x), y(v.y) {};
	

};


struct Line {
	Line() : a(0), b(0), c(0) {};
	Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};
	int a, b, c;
};


struct Rect {
	int x, y;
	int w, h;

	Rect() {};
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
	void SetVec2Pos(Vector2 pos) { x = pos.x; y = pos.y; };

	void Init(int _x, int _y, int _w, int _h) { x = _x; y = _y; w = _w; h = _h; }

	inline bool operator==(Rect a) {
		return  ((a.x == x && a.y == y) && (a.w == w && a.h == h));
	}
};

struct Color {
	int r, g, b, a;

	Color() {};
	Color(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};

	void Init(int _r, int _g, int _b, int _a) { r = _r; g = _g; b = _b; a = _a; }
};

struct Font {
	std::string id;
	std::string path;
	int size;

	Font() {};
	Font(std::string _id, std::string _path, int _size) : id(_id), path(_path), size(_size) {};

	void Init(std::string _id, std::string _path, int _size) { id = _id; path = _path;  size = _size; };
};

struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;

	void Init(std::string _id, std::string _text, Color _color) { id = _id; text = _text; color = _color; }

};

