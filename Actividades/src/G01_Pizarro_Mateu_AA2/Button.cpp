#include "Button.h"

void Button::Init(Color _c, Color _h, Font _font, Rect _rect, Text _text)
{
	c = _c;
	h = _h;
	font = _font;
	rect = _rect;
	text = _text;

}


bool Button::MouseColliding(Rect mouse)
{

	return mouse.x > rect.x && mouse.x < rect.x + rect.w
		&& mouse.y > rect.y && mouse.y < rect.y + rect.h;
}
