#include "HUD.h"

HUD::HUD(Renderer *renderer)
{
	font.Init("fuente", "..\..\res\ttf\Gameplay.ttf", 80);
	renderer->LoadFont(font);
	renderer->LoadTextureText(font.id, scoreText);

}

void HUD::Update()
{


}

void HUD::Draw()
{


}
