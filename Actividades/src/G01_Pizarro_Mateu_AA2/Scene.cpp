#include "Scene.h"

Scene::Scene()
{
	buttons[PLAY_SOUND].Init({ 255, 255, 255, 255 }, { 255, 0, 0, 255 }, "SoUnD oN", "sOuNd On",
		{ "Sound", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ SCREEN_WIDTH / 3, 3 * SCREEN_HEIGHT / 5, 200, 50 });
	buttons[(int)MENU_PLAY].Init({ 255, 0, 0, 255 }, { 255, 0, 0, 255 }, "play", "PLAY",
		{ "Play", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ 2 * SCREEN_WIDTH / 5, (int)(1.8f * SCREEN_HEIGHT / 7), 230, 65 });
	buttons[(int)MENU_RANKING].Init({ 255, 0, 0, 255 }, { 255, 0, 0, 255 }, "ranking", "RANKING",
		{ "Ranking", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ (int)(1.95f * SCREEN_WIDTH / 5) , 3 * SCREEN_HEIGHT / 7, 250, 50 });
	buttons[(int)MENU_SOUND].Init({ 255, 0, 0, 255 }, { 255, 0, 0, 255 }, "sound on", "SOUND ON",
		{ "Sound", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ (int)(1.8f * SCREEN_WIDTH / 5), 4 * SCREEN_HEIGHT / 7, 300, 50 });
	buttons[(int)MENU_EXIT].Init({ 255, 0, 0, 255 }, { 255, 0, 0, 255 }, "exit", "EXIT",
		{ "Exit", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ (int)(2.05f * SCREEN_WIDTH / 5), 5 * SCREEN_HEIGHT / 7, 200, 50 });

}

void Scene::Update(Renderer *)
{
}

void Scene::Load(Renderer *)
{
}

void Scene::Draw(Renderer *)
{
}

void Scene::Load(Renderer *, std::vector<std::vector<Objects*>>&, Map &, Player *, Inky *inky, Clyde *clyde)
{
}

void Scene::Update(Renderer *, std::vector<std::vector<Objects*>>&, Player *, Clyde *, Inky *, std::vector<bool>&, bool, bool, Rect &, bool &)
{
}

void Scene::Draw(Renderer *, std::vector<std::vector<Objects*>>&, Map &, HUD &, Player *, Clyde *, Inky *, bool, bool, Rect &)
{
}

void Scene::Update(Renderer *, Rect &)
{
}

void SplashScreen::Update(Renderer *renderer)
{
}

void SplashScreen::Draw(Renderer *renderer)
{
	Uint32 frameStart, frameTime;
	Rect splashScreenPacManRect, splashScreenPacManRectPos;
	int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
	int frameTimeSprite = 0;

	splashScreenPacManRect.x = 4 * frameWidth; splashScreenPacManRect.y = 0;
	splashScreenPacManRect.w = frameWidth; splashScreenPacManRect.h = frameHeight;
	splashScreenPacManRectPos.x = 0; splashScreenPacManRectPos.y =  SCREEN_HEIGHT / 15;
	splashScreenPacManRectPos.w = SCREEN_WIDTH ; splashScreenPacManRectPos.h =  SCREEN_HEIGHT;

	time_t start = clock() + SPLASH_SCREEN_TIME;
	while (clock() < start)
	{
		frameTimeSprite++;
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
		splashScreenPacManRectPos.x += 20;
		if (FPS / frameTimeSprite <= 9)
		{
			splashScreenPacManRect.x += frameWidth;
			if (splashScreenPacManRect.x >= frameWidth * 6)
			{
				splashScreenPacManRect.x = 4 * frameWidth;
			}
		}
		renderer->Clear();
		renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(splashScreenPacManRect), Utils::RectToSDL_Rect(splashScreenPacManRectPos));
		renderer->Render();
	}
}

void Menu::Update(Renderer *renderer, Rect &mouse)
{
	for (int i = 1; i < static_cast<int>(COUNT); i++)
		buttons[i].ChangeHover(mouse);
		
}

void Menu::Load(Renderer *renderer)
{
}

void Menu::Draw(Renderer *renderer)
{
	for (int i = 1; i < static_cast<int>(COUNT); i++) {
		renderer->LoadFont(buttons[i].font);
		renderer->LoadTextureText(buttons[i].font.id, buttons[i].text);
		renderer->PushImage(buttons[i].font.id, Utils::RectToSDL_Rect(buttons[i].rect));
	}
}

void Play::Update(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Player *player, Clyde *clyde, Inky *inky, std::vector<bool> &keys, bool paused, bool running, Rect &mouse, bool &isClicked)
{
	if (!paused && running)
	{
		//Moure Player 
		player->Move(keys, o, clyde, inky);
		//Moure Enemics 
		clyde->Move(player->dir, o);
		inky->Move(player->dir, o);
		//Recollir power ups i punts 


		//Animacions
		int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
		int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
		if (player->rect.y == 0 && player->hasHittedEnemy) {
			player->rect.x = 4 * frameWidth;
			player->rect.y = 4 * frameHeight;

		}
		player->frameTimeSprite++;
		if (FPS / player->frameTimeSprite <= 9) {
			if (player->hasHittedEnemy)
			{
				player->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 7 && player->rect.y == frameHeight * 4)
				{
					player->rect.x = 0;
					player->rect.y = 5 * frameHeight;
				}
				else if (player->rect.x >= frameWidth * 7 && player->rect.y == frameHeight * 5)
				{
					player->rect.x = 6 * frameWidth;
					player->rect.y = 0 * frameHeight;
					player->dead = true;
				}
			}
			else if (player->dir == Direction::NONE || player->dir == Direction::RIGHT)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if ((player->rect.x >= frameWidth * 6) || (clyde->rect.x >= frameWidth * 8)
					|| (inky->rect.x >= frameWidth * 6))
				{
					player->rect.x = 4 * frameWidth;
					clyde->rect.x = 6 * frameWidth;
					inky->rect.x = 4 * frameWidth;
				}
			}
			else if (player->dir == Direction::LEFT)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 8 || (clyde->rect.x >= frameWidth * 6)
					|| (inky->rect.x >= frameWidth * 8))
				{
					player->rect.x = 6 * frameWidth;
					clyde->rect.x = 4 * frameWidth;
					inky->rect.x = 6 * frameWidth;
				}
			}
			else if (player->dir == Direction::UP)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 2 || (clyde->rect.x >= frameWidth * 4)
					|| (inky->rect.x >= frameWidth * 2))
				{
					player->rect.x = 0;
					clyde->rect.x = 2 * frameWidth;
					inky->rect.x = 0;
				}
			}
			else if (player->dir == Direction::DOWN)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 4 || (clyde->rect.x >= frameWidth * 2)
					|| (inky->rect.x >= frameWidth * 4))
				{
					player->rect.x = 2 * frameWidth;
					clyde->rect.x = 0;
					inky->rect.x = 2 * frameWidth;
				}
			}

		}
	}

	else {
		buttons[PLAY_SOUND].ChangeHover(mouse);
	}
}

void Play::Load(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, Player *player, Inky *inky, Clyde *clyde)
{
	player->Reinit(renderer);
	inky->ReinitPos();
	clyde->ReinitPos();
	map.Reinit(renderer, o);
}

void Play::Draw(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, HUD &hud, Player *player, Clyde *clyde, Inky *inky, bool paused, bool running, Rect &mouse)
{
	Rect fadedSpriteRect, fadedSpritePos;
	map.Draw(renderer, o);
	clyde->Draw(renderer);
	inky->Draw(renderer);
	player->Draw(renderer);
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
		renderer->LoadFont(buttons[PLAY_SOUND].font);

		renderer->LoadTextureText(pausedFontStop.id, pausedFontStopText);
		renderer->LoadTextureText(pausedFont1.id, pausedFontText1);
		renderer->LoadTextureText(pausedFont2.id, pausedFontText2);
		renderer->LoadTextureText(buttons[PLAY_SOUND].font.id, buttons[PLAY_SOUND].text);

		renderer->PushImage(pausedFontStop.id, Utils::RectToSDL_Rect(pausedFontStopRect));
		renderer->PushImage(pausedFont1.id, Utils::RectToSDL_Rect(pausedFontRect1));
		renderer->PushImage(pausedFont2.id, Utils::RectToSDL_Rect(pausedFontRect2));
		renderer->PushImage(buttons[PLAY_SOUND].font.id, Utils::RectToSDL_Rect(buttons[PLAY_SOUND].rect));

	}
	else if (!running) {
		renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(fadedSpriteRect), Utils::RectToSDL_Rect(fadedSpritePos));

		textColor.Init(255, 0, 0, 255);
		notRunningFont1.Init("Press_Space", "../../res/ttf/PAC-FONT.TTF", 60);
		notRunningFont2.Init("To_Start", "../../res/ttf/PAC-FONT.TTF", 60);

		notRunningRect1.Init(SCREEN_WIDTH / 5, 2 * SCREEN_HEIGHT / 5, 400, 60);
		notRunningRect2.Init(SCREEN_WIDTH / 5, 5 * SCREEN_HEIGHT / 10, 400, 60);

		notRunningText1.Init(notRunningFont1.id, "PrEsS SpAcE", textColor);
		notRunningText2.Init(notRunningFont2.id, "To StArT........", textColor);

		renderer->LoadFont(notRunningFont1);
		renderer->LoadFont(notRunningFont2);

		renderer->LoadTextureText(notRunningFont1.id, notRunningText1);
		renderer->LoadTextureText(notRunningFont2.id, notRunningText2);

		renderer->PushImage(notRunningFont1.id, Utils::RectToSDL_Rect(notRunningRect1));
		renderer->PushImage(notRunningFont2.id, Utils::RectToSDL_Rect(notRunningRect2));

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
