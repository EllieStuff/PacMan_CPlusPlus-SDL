#pragma once
#include "Constants.h"
#include "Types.h"
#include"Utils.h"

class Button {
public:
	Color c;	//Color
	Color h;	//Hover
	Font font;
	Rect rect;
	Text text;

	Button() {};
	Button(Color _c, Color _h, Font _font, Rect _rect, Text _text) : c(_c), h(_h), font(_font), rect(_rect), text(_text) {};

	void Init(Color _c, Color _h, Font _font, Rect _rect, Text _text);

	void ChangeHover(Rect mouse);

	bool Used(Rect mouse, bool);

	bool MouseColliding(Rect mouse);

};