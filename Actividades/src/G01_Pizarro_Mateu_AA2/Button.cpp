#include "Button.h"

void Button::Init(Color _c, Color _h, std::string _t, std::string _hoverTFont, Font _font, Rect _rect)
{
	c = _c;
	h = _h;
	t = _t;
	hoverT = _hoverTFont;
	font = _font;
	rect = _rect;
	text.text = t;
	text.id = font.id;
	text.color = c;
}

void Button::ChangeHover(InputHandle &keyboard)
{
	if (MouseColliding(keyboard))
	{
		text.color = h;
		text.text = t;
	}
	else
	{
		text.color = c;
		text.text = hoverT;
	}

}

bool Button::Used(InputHandle &keyboard)
{

	return MouseColliding(keyboard) && keyboard.isClicked;
}


bool Button::MouseColliding(InputHandle &keyboard)
{

	return keyboard.cursor.x > rect.x && keyboard.cursor.x < rect.x + rect.w
		&& keyboard.cursor.y > rect.y && keyboard.cursor.y < rect.y + rect.h;
}

