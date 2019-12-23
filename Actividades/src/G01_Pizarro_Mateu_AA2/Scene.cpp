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

void Scene::Update()
{
}

void Scene::Load()
{
}

void Scene::Draw()
{
}

void Scene::Load(std::vector<std::vector<Objects*>>&, Map &)
{
}

void Scene::Update(std::vector<std::vector<Objects*>>&, std::vector<bool>&, bool, bool, Rect &, bool &)
{
}

void Scene::Draw(std::vector<std::vector<Objects*>>&, Map &, bool, bool, Rect &)
{
}

void Scene::Update(Rect &)
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

void Menu::Update(Rect &mouse)
{
	for (int i = 1; i < static_cast<int>(COUNT); i++)
		buttons[i].ChangeHover(mouse);
		
}

void Menu::Load()
{
}

void Menu::Draw()
{
	for (int i = 1; i < static_cast<int>(COUNT); i++) {
		Renderer::Instance()->LoadFont(buttons[i].font);
		Renderer::Instance()->LoadTextureText(buttons[i].font.id, buttons[i].text);
		Renderer::Instance()->PushImage(buttons[i].font.id, Utils::RectToSDL_Rect(buttons[i].rect));
	}
}

void Play::Update(std::vector<std::vector<Objects*>> &o, std::vector<bool> &keys, bool paused, bool running, Rect &mouse, bool &isClicked)
{
	if (!paused && running)
	{
		//Moure Player 
		Player::Instance()->Move(keys, o);
		//Moure Enemics 
		Clyde::Instance()->Move(Player::Instance()->dir, o);
		Inky::Instance()->Move(Player::Instance()->dir, o);
		//Recollir power ups i punts 


		//Animacions
		int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
		int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
		if (Player::Instance()->rect.y == 0 && Player::Instance()->hasHitEnemy) {
			Player::Instance()->rect.x = 4 * frameWidth;
			Player::Instance()->rect.y = 4 * frameHeight;

		}
		Player::Instance()->frameTimeSprite++;
		if (FPS / Player::Instance()->frameTimeSprite <= 9) {
			if (Player::Instance()->hasHitEnemy)
			{
				Player::Instance()->rect.x += frameWidth;
				if (Player::Instance()->rect.x >= frameWidth * 7 && Player::Instance()->rect.y == frameHeight * 4)
				{
					Player::Instance()->rect.x = 0;
					Player::Instance()->rect.y = 5 * frameHeight;
				}
				else if (Player::Instance()->rect.x >= frameWidth * 7 && Player::Instance()->rect.y == frameHeight * 5)
				{
					Player::Instance()->rect.x = 6 * frameWidth;
					Player::Instance()->rect.y = 0 * frameHeight;
					Player::Instance()->dead = true;
				}
			}
			else if (Player::Instance()->dir == Direction::NONE || Player::Instance()->dir == Direction::RIGHT)
			{
				Player::Instance()->rect.x += frameWidth;
				Clyde::Instance()->rect.x += frameWidth;
				Inky::Instance()->rect.x += frameWidth;
				if ((Player::Instance()->rect.x >= frameWidth * 6) || (Clyde::Instance()->rect.x >= frameWidth * 8)
					|| (Inky::Instance()->rect.x >= frameWidth * 6))
				{
					Player::Instance()->rect.x = 4 * frameWidth;
					Clyde::Instance()->rect.x = 6 * frameWidth;
					Inky::Instance()->rect.x = 4 * frameWidth;
				}
			}
			else if (Player::Instance()->dir == Direction::LEFT)
			{
				Player::Instance()->rect.x += frameWidth;
				Clyde::Instance()->rect.x += frameWidth;
				Inky::Instance()->rect.x += frameWidth;
				if (Player::Instance()->rect.x >= frameWidth * 8 || (Clyde::Instance()->rect.x >= frameWidth * 6)
					|| (Inky::Instance()->rect.x >= frameWidth * 8))
				{
					Player::Instance()->rect.x = 6 * frameWidth;
					Clyde::Instance()->rect.x = 4 * frameWidth;
					Inky::Instance()->rect.x = 6 * frameWidth;
				}
			}
			else if (Player::Instance()->dir == Direction::UP)
			{
				Player::Instance()->rect.x += frameWidth;
				Clyde::Instance()->rect.x += frameWidth;
				Inky::Instance()->rect.x += frameWidth;
				if (Player::Instance()->rect.x >= frameWidth * 2 || (Clyde::Instance()->rect.x >= frameWidth * 4)
					|| (Inky::Instance()->rect.x >= frameWidth * 2))
				{
					Player::Instance()->rect.x = 0;
					Clyde::Instance()->rect.x = 2 * frameWidth;
					Inky::Instance()->rect.x = 0;
				}
			}
			else if (Player::Instance()->dir == Direction::DOWN)
			{
				Player::Instance()->rect.x += frameWidth;
				Clyde::Instance()->rect.x += frameWidth;
				Inky::Instance()->rect.x += frameWidth;
				if (Player::Instance()->rect.x >= frameWidth * 4 || (Clyde::Instance()->rect.x >= frameWidth * 2)
					|| (Inky::Instance()->rect.x >= frameWidth * 4))
				{
					Player::Instance()->rect.x = 2 * frameWidth;
					Clyde::Instance()->rect.x = 0;
					Inky::Instance()->rect.x = 2 * frameWidth;
				}
			}

		}
	}

	else {
		buttons[PLAY_SOUND].ChangeHover(mouse);
	}
}

void Play::Load(std::vector<std::vector<Objects*>> &o, Map &map)
{
	Player::Instance()->Reinit();
	Inky::Instance()->ReinitPos();
	Clyde::Instance()->ReinitPos();
	map.Reinit(o);
}

void Play::Draw(std::vector<std::vector<Objects*>> &o, Map &map, bool paused, bool running, Rect &mouse)
{
	HUD hud;
	Rect fadedSpriteRect, fadedSpritePos;
	map.Draw(o);
	Clyde::Instance()->Draw();
	Inky::Instance()->Draw();
	Player::Instance()->Draw();
	hud.Update();
	hud.Draw();

	int frameWidth = Renderer::Instance()->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = Renderer::Instance()->GetTextureSize("PacmanSheet").y / 8;
	fadedSpriteRect.x = 0; fadedSpriteRect.y = 7 * frameHeight;
	fadedSpriteRect.w = frameWidth; fadedSpriteRect.h = frameHeight;
	fadedSpritePos.x = fadedSpritePos.y = 0;
	fadedSpritePos.w = SCREEN_WIDTH; fadedSpritePos.h = SCREEN_HEIGHT;
	if (paused)
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
	else if (!running) {
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

void Ranking::Update()
{
	//Necessitem un Update del ranking?

}

void Ranking::Load()
{


}

void Ranking::Draw()
{


}

void Exit::Load()
{


}
