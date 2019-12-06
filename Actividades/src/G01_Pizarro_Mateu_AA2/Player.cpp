#include "Player.h"

void Player::Move(std::vector<bool> keys)
{
	if (keys[SDLK_w]) pos.y -= PIXELS_PER_FRAME;
	if (keys[SDLK_s]) pos.y += PIXELS_PER_FRAME;
	if (keys[SDLK_a]) pos.x -= PIXELS_PER_FRAME;
	if (keys[SDLK_d]) pos.x += PIXELS_PER_FRAME;

}

bool Player::HitsWall(Direction dir, std::vector<std::vector<Objects*>> o)
{


	return false;
}
