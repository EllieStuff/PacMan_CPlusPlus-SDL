#pragma once
#include "Constants.h"
#include "Types.h"
#include"Utils.h"

class Button {
public:
	Color c;
	Font font;
	Rect rect;
	Text text;

	Button(Color _c, Font _font, Rect _rect, Text _text) : c(_c), font(_font), rect(_rect), text(_text) {};

	void Init(Color _c, Font _font, Rect _rect, Text _text);

private:
	void Use();

};