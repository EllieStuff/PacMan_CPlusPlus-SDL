#pragma once

struct Vec2 {
	int x, y;

	Vec2(int _x, int _y){
		x = _x;
		y = _y;

	}

};

struct Vec2Square {
	int x, y, w, h;

	Vec2Square(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;

	}

};
