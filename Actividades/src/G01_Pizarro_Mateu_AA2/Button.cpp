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

void Button::ChangeHover(Rect mouse)
{
	if (MouseColliding(mouse))
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

bool Button::Used(Rect mouse, bool isClicked)
{

	return MouseColliding(mouse) && isClicked;
}


bool Button::MouseColliding(Rect mouse)
{

	return mouse.x > rect.x && mouse.x < rect.x + rect.w
		&& mouse.y > rect.y && mouse.y < rect.y + rect.h;
}

