#include "Scene.h"

void Scene::Update(Renderer *)
{
}

void Scene::Load(Renderer *)
{
}

void Scene::Draw(Renderer *)
{
}

void Scene::Load(Renderer *, std::vector<std::vector<Objects*>>&, Map &, Player *)
{
}


void Scene::Update(Renderer *, std::vector<std::vector<Objects*>>&, Player *, Clyde *, Inky *, std::vector<bool>&, bool, Rect &, bool &, Button &)
{
}

void Scene::Draw(Renderer *, std::vector<std::vector<Objects*>>&, Map &, HUD &, Player *, Clyde *, Inky *, bool, Rect &, Button &)
{
}

void SplashScreen::Update(Renderer *renderer)	//Nota: Es provisional, currar-s'ho una miqueta plis xD
{
	//Sleep(3);

	//state = SceneState::GO_TO_MENU;
}

void SplashScreen::Draw(Renderer *renderer)
{
	//renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(_o[i][j]->rect), RectToSDL_Rect(_o[i][j]->rectPos));

}

void Menu::Update(Renderer *renderer)
{
	/*if () state = SceneState::GO_TO_PLAY;
	else if () state = SceneState::GO_TO_MENU;
	else if () state = SceneState::GO_TO_RANKING;*/

}

void Menu::Load(Renderer *renderer)
{


}

void Menu::Draw(Renderer *renderer)
{


}

void Play::Update(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Player *player, Clyde *clyde, Inky *inky, std::vector<bool> &keys, bool paused, Rect &mouse, bool &isClicked, Button &soundB)
{
	if (!paused)
	{
		//Moure Player 
		player->Move(keys, o, clyde->pos, inky->pos);
		//Moure Enemics 
		clyde->Move(player->dir, o);
		inky->Move(player->dir, o);
		//Recollir power ups i punts 

	}
	else {
		soundB.Init({ 255, 255, 255, 255 }, { 255, 0, 0, 255 }, { "Sound", "../../res/ttf/PAC-FONT.TTF", 90 },
			{ SCREEN_WIDTH / 3, 3 * SCREEN_HEIGHT / 5, 200, 30 }, { "Sound", "SoUnD oN", { 255, 255, 255, 255 } });
		soundB.ChangeHover(mouse);

	}
		
}


void Play::Load(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, Player *player)
{
	map.Create(renderer, o);
	player->Reinit();
	map.Reinit(renderer, o);

	//Posar enemies i player

}

void Play::Draw(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, HUD &hud, Player *player, Clyde *clyde, Inky *inky, bool paused, Rect &mouse, Button &soundB)
{
	Rect fadedSpriteRect, fadedSpritePos;
	map.Draw(renderer, o);
	player->Draw(renderer);
	clyde->Draw(renderer);
	inky->Draw(renderer);
	hud.Update(renderer, player);
	hud.Draw(renderer, player);
	int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
	fadedSpriteRect.x = 0; fadedSpriteRect.y = 7 * frameHeight;
	fadedSpriteRect.w = frameWidth; fadedSpriteRect.h = frameHeight;
	fadedSpritePos.x = fadedSpritePos.y = 0;
	fadedSpritePos.w = SCREEN_WIDTH; fadedSpritePos.h = SCREEN_HEIGHT;
	if (paused)
	{
		renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(fadedSpriteRect), Utils::RectToSDL_Rect(fadedSpritePos));
		textColor.Init(255, 0, 0, 255);
		pausedFontStop.Init("STOP", "../../res/ttf/PAC-FONT.TTF", 60);
		pausedFont1.Init("PressSpace", "../../res/ttf/PAC-FONT.TTF", 36);
		pausedFont2.Init("PressSpace2", "../../res/ttf/PAC-FONT.TTF", 36);
		pausedFontStopText.Init(pausedFontStop.id, "StOp", textColor);
		pausedFontText1.Init(pausedFont1.id, "PrEsS SpAcE", textColor);
		pausedFontText2.Init(pausedFont2.id, "tO rElEaSe", textColor);
		pausedFontStopRect.Init((SCREEN_WIDTH / 2) - HUD_WIDTH, HUD_EDGES * 3, 340, 120);
		pausedFontRect1.Init((SCREEN_WIDTH / 2) - HUD_WIDTH + TILES_PIXEL / 2, (HUD_EDGES * 3) * 4, 280, 42);
		pausedFontRect2.Init((SCREEN_WIDTH / 2) - HUD_WIDTH + TILES_PIXEL / 2, (HUD_EDGES * 3) * 5, 280, 42);
		renderer->LoadFont(pausedFontStop);
		renderer->LoadFont(pausedFont1);
		renderer->LoadFont(pausedFont2);
		renderer->LoadFont(soundB.font);
		renderer->LoadTextureText(pausedFontStop.id, pausedFontStopText);
		renderer->LoadTextureText(pausedFont1.id, pausedFontText1);
		renderer->LoadTextureText(pausedFont2.id, pausedFontText2);
		renderer->LoadTextureText(soundB.font.id, soundB.text);
		renderer->PushImage(pausedFontStop.id, Utils::RectToSDL_Rect(pausedFontStopRect));
		renderer->PushImage(pausedFont1.id, Utils::RectToSDL_Rect(pausedFontRect1));
		renderer->PushImage(pausedFont2.id, Utils::RectToSDL_Rect(pausedFontRect2));
		renderer->PushImage(soundB.font.id, Utils::RectToSDL_Rect(soundB.rect));

	}
}

void Ranking::Update(Renderer *renderer)
{
	//Necessitem un Update del ranking?

}

void Ranking::Load(Renderer *renderer)
{


}

void Ranking::Draw(Renderer *renderer)
{


}

void Exit::Load(Renderer *renderer)
{


}
