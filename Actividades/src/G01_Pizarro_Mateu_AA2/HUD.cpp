#include "HUD.h"


HUD::HUD(Player *player)
{
	textColor.Init(0, 0, 0, 0);
	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	bgRect.Init(7 * frameWidth, 6 * frameHeight, frameWidth, frameHeight);
	bgPos.Init(SCREEN_WIDTH - HUD_WIDTH, 0, HUD_WIDTH, SCREEN_HEIGHT);
	font.Init("GameplayFont", "../../res/ttf/Gameplay.ttf", 80);
	scoreText.Init(font.id, Utils::AddZerosInFrontOfStr(player->score, 4), textColor);
	score.Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_EDGES * 3, 160, 80);
	Renderer::Instance()->LoadFont(font);
	Renderer::Instance()->LoadTextureText(font.id, scoreText);

	//Lives
	for (int i = 0; i < player->livesLeft; i++) {
		lives[i][SPRITE].Init((SCREEN_WIDTH - HUD_WIDTH - HUD_EDGES / 3 + (i * TILES_PIXEL * 2)), (SCREEN_HEIGHT - HUD_EDGES - (TILES_PIXEL * 2)), TILES_PIXEL * 2, TILES_PIXEL * 2);
		lives[i][RECT].Init(7 * frameWidth, 0 * frameHeight, frameWidth, frameHeight);
	}
	
}

void HUD::Update(Player *player)
{
	scoreText.Init(font.id, Utils::AddZerosInFrontOfStr(player->score, 4), textColor);
	score.Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_EDGES * 3, 160, 80);
	Renderer::Instance()->LoadFont(font);
	Renderer::Instance()->LoadTextureText(font.id, scoreText);

}

void HUD::Draw(Player *player)
{
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(bgRect), Utils::RectToSDL_Rect(bgPos));
	for (int i = 0; i < player->livesLeft; i++) {
		Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(lives[i][RECT]), Utils::RectToSDL_Rect(lives[i][SPRITE]));
	}
	Renderer::Instance()->PushImage(font.id, Utils::RectToSDL_Rect(score));
}
