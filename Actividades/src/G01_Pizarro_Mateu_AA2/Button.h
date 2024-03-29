#pragma once
#include "Constants.h"
#include "Types.h"
#include"Utils.h"
#include "InputHandle.h"

class Button {
public:
	Color c;	//Color
	Color h;	//Hover
	Font font;
	Rect rect;
	Text text;
	std::string t, hoverT;
	//Constructor
	Button() {};
	Button(Color _c, Color _h, std::string _t, std::string _hoverT, Font _font, Rect _rect, Text _text) : c(_c), h(_h), t(_t), hoverT(_hoverT), font(_font), rect(_rect), text(_text) {};
	//Functions
	void Init(Color _c, Color _h, std::string _t, std::string _hoverT, Font _font, Rect _rect);
	void ChangeHover(InputHandle &);
	bool Used(InputHandle &);
	bool MouseColliding(InputHandle &);
};