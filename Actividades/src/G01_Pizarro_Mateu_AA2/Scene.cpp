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
	buttons[(int)RANKING_EXIT].Init({ 255, 0, 0, 255 }, { 255, 0, 0, 255 }, "exit", "EXIT",
		{ "Exit", "../../res/ttf/PAC-FONT.TTF", 90 },
		{ SCREEN_WIDTH - 200 - RANKING_EDGES, SCREEN_HEIGHT - 50 - RANKING_EDGES, 200, 50 });

}

void Scene::Update()
{
}

void Scene::Load()
{
}

void Scene::Draw()
{
}

void Scene::Load(std::vector<std::vector<Objects*>>&, Map &, Player *, Inky *inky, Clyde *clyde, Blinky *blinky, Fruit &)
{
}

void Scene::Update(std::vector<std::vector<Objects*>>&, Player *, Clyde *, Inky *, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &, HUD &hud)
{
}

void Scene::Draw(std::vector<std::vector<Objects*>>&, Map &, Player *, Clyde *, Inky *, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &, HUD &hud)
{
}

void Scene::Load(RankingData & ranking)
{
}

void Scene::Update(InputHandle &keyboard)
{
}

void Scene::Draw(RankingData & ranking)
{
}

void SplashScreen::Update()
{
}

void SplashScreen::Draw()
{
	Uint32 frameStart, frameTime;
	Rect splashScreenPacManRect, splashScreenPacManRectPos;
	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
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
		Renderer::Instance()->Clear();
		Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(splashScreenPacManRect), Utils::RectToSDL_Rect(splashScreenPacManRectPos));
		Renderer::Instance()->Render();
	}
}

void Menu::Update(InputHandle &keyboard)
{
	for (int i = 1; i < static_cast<int>(COUNT); i++)
		buttons[i].ChangeHover(keyboard);
		
}

void Menu::Load()
{
}

void Menu::Draw()
{
	for (int i = 2; i < static_cast<int>(COUNT); i++) {
		Renderer::Instance()->LoadFont(buttons[i].font);
		Renderer::Instance()->LoadTextureText(buttons[i].font.id, buttons[i].text);
		Renderer::Instance()->PushImage(buttons[i].font.id, Utils::RectToSDL_Rect(buttons[i].rect));
	}
}

void Play::Update(std::vector<std::vector<Objects*>> &o, Player *player, Clyde *clyde, Inky *inky, Blinky *blinky, PlayAuxiliars &pAux, InputHandle &keyboard, Fruit &fruit, HUD &hud)
{
	if (!pAux.paused && pAux.running)
	{
		if (pAux.timeDifChecked) {
			if (player->hasPowerUp)
				player->powerUpEnd = clock() + pAux.powerUpTDif;
			if (fruit.publicType == FruitTypes::EMPTY)
				fruit.waitEnd = clock() + pAux.fruitTDif;

			pAux.timeDifChecked = false;

		}


		//Moure Player 
		player->Move(keyboard.keys, o, clyde, inky, blinky, fruit);
		//Moure Enemics 
		clyde->Move(player->dir, o);
		inky->Move(player->dir, o);
		blinky->Move(o);
		hud.Update(player);
		//Crear fruita
		fruit.Instantiate();

		//Animacions
		int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
		int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
		if (player->rect.y == 0 && player->hasHitEnemy) {
			player->rect.x = 4 * frameWidth;
			player->rect.y = 4 * frameHeight;

		}
		player->frameTimeSprite++;
		if (FPS / player->frameTimeSprite <= 9) {
			if (player->hasHitEnemy)
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
			else if (!player->hasPowerUp)
			{
				if (player->dir == Direction::NONE || player->dir == Direction::RIGHT)
				{
					clyde->rect.x = 6 * frameWidth;
					inky->rect.x = 4 * frameWidth;
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
					clyde->rect.x = 4 * frameWidth;
					inky->rect.x = 6 * frameWidth;
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
					clyde->rect.x = 2 * frameWidth;
					inky->rect.x = 0;
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
					clyde->rect.x = 0;
					inky->rect.x = 2 * frameWidth;
					player->rect.x += frameWidth;
					clyde->rect.x += frameWidth;
					inky->rect.x += frameWidth;
					blinky->rect.x += frameWidth;
					if (player->rect.x >= frameWidth * 4 || (clyde->rect.x >= frameWidth * 2)
						|| (inky->rect.x >= frameWidth * 4))
					{
						player->rect.x = 2 * frameWidth;
						clyde->rect.x = 0;
						inky->rect.x = 2 * frameWidth;
					}
				}
				if (blinky->dir == Direction::RIGHT)
				{
					blinky->rect.x = 4 * frameWidth;
					blinky->rect.x += frameWidth;
					if (blinky->rect.x >= frameWidth * 6)
					{
						blinky->rect.x = 4 * frameWidth;
					}
				}
				else if (blinky->dir == Direction::LEFT)
				{
					blinky->rect.x = 6 * frameWidth;
					blinky->rect.x += frameWidth;
					if (blinky->rect.x >= frameWidth * 8)
					{
						blinky->rect.x = 6 * frameWidth;
					}
				}
				else if (blinky->dir == Direction::UP)
				{
					blinky->rect.x = 0;
					blinky->rect.x += frameWidth;
					if (blinky->rect.x >= frameWidth * 2)
					{
						blinky->rect.x = 0;
					}
				}
				else if (blinky->dir == Direction::DOWN)
				{
					blinky->rect.x = 2 * frameWidth;
					blinky->rect.x += frameWidth;
					if (blinky->rect.x >= frameWidth * 4)
					{
						blinky->rect.x = 2 * frameWidth;
					}
				}
			}
			else if (player->hasPowerUp)
			{
				if (player->dir == Direction::NONE || player->dir == Direction::RIGHT)
				{
					player->rect.x += frameWidth;
					if ((player->rect.x >= frameWidth * 6))
					{
						player->rect.x = 4 * frameWidth;
					}
				}
				else if (player->dir == Direction::LEFT)
				{
					player->rect.x += frameWidth;
					if (player->rect.x >= frameWidth * 8 )
					{
						player->rect.x = 6 * frameWidth;
					}
				}
				else if (player->dir == Direction::UP)
				{
					player->rect.x += frameWidth;
					if (player->rect.x >= frameWidth * 2 )
					{
						player->rect.x = 0;
					}
				}
				else if (player->dir == Direction::DOWN)
				{
					player->rect.x += frameWidth;
					if (player->rect.x >= frameWidth * 4)
					{
						player->rect.x = 2 * frameWidth;
					}
				}
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				blinky->rect.x += frameWidth;
				if (clyde->rect.x >= frameWidth * 4 || inky->rect.x >= frameWidth * 4 || blinky->rect.x >= frameWidth * 4)
				{
					clyde->rect.x = 0;
					inky->rect.x = 0;
					blinky->rect.x = 0;
				}
			}
		}
	}
	else {
		buttons[PLAY_SOUND].ChangeHover(keyboard);
		if (!pAux.timeDifChecked) {
			if (player->hasPowerUp && player->powerUpEnd > clock())
				pAux.powerUpTDif = player->powerUpEnd - clock();
			else pAux.powerUpTDif = 0;

			if (fruit.publicType == FruitTypes::EMPTY && fruit.waitEnd > clock())
				pAux.fruitTDif = fruit.waitEnd - clock();
			else pAux.fruitTDif = 0;

			pAux.timeDifChecked = true;

		}
	}
}

void Play::Load(std::vector<std::vector<Objects*>> &o, Map &map, Player *player, Inky *inky, Clyde *clyde, Blinky *blinky, Fruit &fruit)
{
	player->Reinit(map.maxScore);
	inky->Reinit();
	clyde->Reinit();
	blinky->Reinit();
	map.Reinit(o);
	fruit.Reinit();

}

void Play::Draw(std::vector<std::vector<Objects*>> &o, Map &map, Player *player, Clyde *clyde, Inky *inky, Blinky *blinky, PlayAuxiliars &pAux, InputHandle &keyboard, Fruit &fruit, HUD &hud)
{
	Rect fadedSpriteRect, fadedSpritePos;
	map.Draw(o);
	fruit.Draw();
	clyde->Draw();
	inky->Draw();
	blinky->Draw();
	player->Draw();
	hud.Draw(player);

	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	fadedSpriteRect.x = 0; fadedSpriteRect.y = 7 * frameHeight;
	fadedSpriteRect.w = frameWidth; fadedSpriteRect.h = frameHeight;
	fadedSpritePos.x = fadedSpritePos.y = 0;
	fadedSpritePos.w = SCREEN_WIDTH; fadedSpritePos.h = SCREEN_HEIGHT;
	if (pAux.paused)
	{
		Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(fadedSpriteRect), Utils::RectToSDL_Rect(fadedSpritePos));

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

		Renderer::Instance()->LoadFont(pausedFontStop);
		Renderer::Instance()->LoadFont(pausedFont1);
		Renderer::Instance()->LoadFont(pausedFont2);
		Renderer::Instance()->LoadFont(buttons[PLAY_SOUND].font);

		Renderer::Instance()->LoadTextureText(pausedFontStop.id, pausedFontStopText);
		Renderer::Instance()->LoadTextureText(pausedFont1.id, pausedFontText1);
		Renderer::Instance()->LoadTextureText(pausedFont2.id, pausedFontText2);
		Renderer::Instance()->LoadTextureText(buttons[PLAY_SOUND].font.id, buttons[PLAY_SOUND].text);

		Renderer::Instance()->PushImage(pausedFontStop.id, Utils::RectToSDL_Rect(pausedFontStopRect));
		Renderer::Instance()->PushImage(pausedFont1.id, Utils::RectToSDL_Rect(pausedFontRect1));
		Renderer::Instance()->PushImage(pausedFont2.id, Utils::RectToSDL_Rect(pausedFontRect2));
		Renderer::Instance()->PushImage(buttons[PLAY_SOUND].font.id, Utils::RectToSDL_Rect(buttons[PLAY_SOUND].rect));

	}
	else if (!pAux.running) {
		Renderer::Instance()->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(fadedSpriteRect), Utils::RectToSDL_Rect(fadedSpritePos));

		textColor.Init(255, 0, 0, 255);
		notRunningFont1.Init("Press_Space", "../../res/ttf/PAC-FONT.TTF", 60);
		notRunningFont2.Init("To_Start", "../../res/ttf/PAC-FONT.TTF", 60);

		notRunningRect1.Init(SCREEN_WIDTH / 5, 2 * SCREEN_HEIGHT / 5, 400, 60);
		notRunningRect2.Init(SCREEN_WIDTH / 5, 5 * SCREEN_HEIGHT / 10, 400, 60);

		notRunningText1.Init(notRunningFont1.id, "PrEsS SpAcE", textColor);
		notRunningText2.Init(notRunningFont2.id, "To StArT........", textColor);

		Renderer::Instance()->LoadFont(notRunningFont1);
		Renderer::Instance()->LoadFont(notRunningFont2);

		Renderer::Instance()->LoadTextureText(notRunningFont1.id, notRunningText1);
		Renderer::Instance()->LoadTextureText(notRunningFont2.id, notRunningText2);

		Renderer::Instance()->PushImage(notRunningFont1.id, Utils::RectToSDL_Rect(notRunningRect1));
		Renderer::Instance()->PushImage(notRunningFont2.id, Utils::RectToSDL_Rect(notRunningRect2));

	}
}


void Ranking::Update(InputHandle &keyboard)
{
	buttons[RANKING_EXIT].ChangeHover(keyboard);

}


void Ranking::Load(RankingData & ranking)
{
	ranking.Load();

}

void Ranking::Draw(RankingData & ranking)
{
	ranking.Draw();
	Renderer::Instance()->LoadFont(buttons[RANKING_EXIT].font);
	Renderer::Instance()->LoadTextureText(buttons[RANKING_EXIT].font.id, buttons[RANKING_EXIT].text);
	Renderer::Instance()->PushImage(buttons[RANKING_EXIT].font.id, Utils::RectToSDL_Rect(buttons[RANKING_EXIT].rect));

}

