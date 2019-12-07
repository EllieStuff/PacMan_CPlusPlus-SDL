#include "HUD.h"

HUD::HUD(Renderer *renderer)
{
	/*Font font;
	Rect score;
	Text scoreText;
	Rect lives[3][static_cast<int>(COUNT)];
	Rect cherry[static_cast<int>(COUNT)];
	Text cherText;
	Rect sb[static_cast<int>(COUNT)];
	Text sbText;
	Rect orange[static_cast<int>(COUNT)];
	Text oranText;*/

	Color c(0, 0, 0, 0);
	renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
	bgRect.Init(7 * frameWidth, 6 * frameHeight, frameWidth, frameHeight);
	bgPos.Init(SCREEN_WIDTH - HUD_WIDTH, 0, HUD_WIDTH, SCREEN_HEIGHT);
	font.Init("GameplayFont", "../../res/ttf/Gameplay.ttf", 80);
	scoreText.Init(font.id, "Score", c);
	score.Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_EDGES, 160, 80);
	renderer->LoadFont(font);
	renderer->LoadTextureText(font.id, scoreText);
	

}

void HUD::Update()
{


}

void HUD::Draw(Renderer *renderer)
{
	renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(bgRect), Utils::RectToSDL_Rect(bgPos));
	renderer->PushImage(font.id, Utils::RectToSDL_Rect(score));

}
