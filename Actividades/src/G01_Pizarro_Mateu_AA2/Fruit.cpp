#include "Fruit.h"

void Fruit::Init(const Rect & _pos)
{
	waitEnd = clock() + FRUITS_FIRST_DELAY;
	pos = _pos;

	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	rect = { 3 * frameWidth, 6 * frameHeight, frameWidth, frameHeight };

}

void Fruit::ChangeFruit()
{
	//Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int newType = rand() % static_cast<int>(FruitTypes::COUNT);
	while (lastType == currentType && static_cast<FruitTypes>(newType) == currentType)
		newType = rand() % static_cast<int>(FruitTypes::COUNT);
	
	lastType = currentType;
	publicType = currentType = static_cast<FruitTypes>(newType);
	//rect.x = newType * frameWidth;
	switch (currentType) {
	case FruitTypes::CHERRY:
		rect.x = 0;
		extraScore = CHERRY_VALUE;

		break;

	case FruitTypes::STRAWBERRY:
		rect.x = 1 * frameWidth;
		extraScore = SB_VALUE;

		break;

	case FruitTypes::ORANGE:
		rect.x = 2 * frameWidth;
		extraScore = ORANGE_VALUE;

		break;

	default:;

	}

}

void Fruit::EraseFruit()
{
	publicType = FruitTypes::EMPTY;

	//Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	rect.x = 3 * frameWidth;
	extraScore = 0;
	waitEnd = clock() + FRUITS_DELAY;

}

void Fruit::Instantiate()
{
	if (publicType == FruitTypes::EMPTY && waitEnd < clock())
		ChangeFruit();
}

void Fruit::Draw()
{
	//Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(rect), Utils::RectToSDL_Rect(pos));

}

void Fruit::Reinit()
{
	///TODO: El reinit no funciona, averiguar perque
	//Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	waitEnd = clock() + FRUITS_FIRST_DELAY;
	//initialized = false;
	rect.x = 3 * (Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8);
	publicType = lastType = currentType = FruitTypes::EMPTY;
	extraScore = 0;

}
