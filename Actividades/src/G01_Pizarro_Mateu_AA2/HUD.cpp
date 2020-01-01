#include "HUD.h"


void HUD::Init(Player *player)
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

	//Cherry
	cherry[POS].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_WIDTH, 80, 80);
	cherry[TEXT].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES + 80, HUD_WIDTH, 80, 80);
	cherry[RECT].Init(0, 6 * frameHeight, frameWidth, frameHeight);
	cherText.Init("CherryId", "X 0", textColor);
	//Strawberry
	sb[POS].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_WIDTH + HUD_EDGES + 80, 80, 80);
	sb[TEXT].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES + 80, HUD_WIDTH + HUD_EDGES + 80, 80, 80);
	sb[RECT].Init(frameWidth, 6 * frameHeight, frameWidth, frameHeight);
	sbText.Init("StrawberryId", "X 0", textColor);
	//Orange
	orange[POS].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_WIDTH + HUD_EDGES + 160, 80, 80);
	orange[TEXT].Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES + 80, HUD_WIDTH + HUD_EDGES + 160, 80, 80);
	orange[RECT].Init(2 * frameWidth, 6 * frameHeight, frameWidth, frameHeight);
	oranText.Init("OrangeId", "X 0", textColor);

	//Lives
	for (int i = 0; i < player->livesLeft; i++) {
		lives[i][POS].Init((SCREEN_WIDTH - HUD_WIDTH - HUD_EDGES / 3 + (i * TILES_PIXEL * 2)), (SCREEN_HEIGHT - HUD_EDGES - (TILES_PIXEL * 2)), TILES_PIXEL * 2, TILES_PIXEL * 2);
		lives[i][RECT].Init(7 * frameWidth, 0 * frameHeight, frameWidth, frameHeight);
	}
	
}

HUD::HUD()
{

}

void HUD::Update(Player *player)
{
	//Score
	scoreText.text = Utils::AddZerosInFrontOfStr(player->score, 4);
	Renderer::Instance()->LoadTextureText(font.id, scoreText);

	//Cherry
	char fruitNum = player->cherries + '0';
	cherText.text = "X ";
	cherText.text += fruitNum;
	Renderer::Instance()->LoadTextureText(font.id, cherText);
	//Strawberry
	fruitNum = player->strawBerries + '0';
	sbText.text = "X ";
	sbText.text += fruitNum;
	Renderer::Instance()->LoadTextureText(font.id, sbText);
	//Orange
	fruitNum = player->oranges + '0';
	oranText.text = "X ";
	oranText.text += fruitNum;
	Renderer::Instance()->LoadTextureText(font.id, oranText);

}

void HUD::Draw(Player *player)
{
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(bgRect), Utils::RectToSDL_Rect(bgPos));
	for (int i = 0; i < player->livesLeft; i++) {
		Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(lives[i][RECT]), Utils::RectToSDL_Rect(lives[i][POS]));
	}
	Renderer::Instance()->PushImage(scoreText.id, Utils::RectToSDL_Rect(score));

	//Cherry
	Renderer::Instance()->PushImage(cherText.id, Utils::RectToSDL_Rect(cherry[TEXT]));
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(cherry[RECT]), Utils::RectToSDL_Rect(cherry[POS]));
	//Strawberry
	Renderer::Instance()->PushImage(sbText.id, Utils::RectToSDL_Rect(sb[TEXT]));
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(sb[RECT]), Utils::RectToSDL_Rect(sb[POS]));
	//Orange
	Renderer::Instance()->PushImage(oranText.id, Utils::RectToSDL_Rect(orange[TEXT]));
	Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(orange[RECT]), Utils::RectToSDL_Rect(orange[POS]));
}
