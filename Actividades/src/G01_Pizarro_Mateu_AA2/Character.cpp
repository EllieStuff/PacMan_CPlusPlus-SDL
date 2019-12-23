#include "Character.h"



Character::Character()
{

}

void Character::SetInitPos(int & _x, int & _y)
{
	initialPos.x = _x;
	initialPos.y = _y;
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

void Character::Update()
{
}

void Character::Draw()
{
}
