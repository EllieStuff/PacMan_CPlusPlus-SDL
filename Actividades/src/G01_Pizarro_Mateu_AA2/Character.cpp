#include "Character.h"



Character::Character()
{

}

void Character::Move()
{
}

bool Character::OnEdge()
{
	return false;
}

void Character::ReinitPos()
{
	pos.x = initialPos.x;
	pos.y = initialPos.y;

}

void Character::Reinit()
{
}

void Character::SetInitPos()
{
	initialPos = Utils::Rect_Vec2(pos);

}

void Character::Update()
{
}

void Character::Draw()
{
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(rect), Utils::RectToSDL_Rect(pos));

}
