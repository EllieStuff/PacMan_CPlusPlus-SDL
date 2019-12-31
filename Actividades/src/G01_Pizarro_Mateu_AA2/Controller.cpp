#include "Controller.h"

Controller::Controller()
{
	scene = new SplashScreen;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		o.push_back({ new Objects });
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			o[i].push_back({ new Objects });
			o[i][j]->tile = MapTiles::POINTS;
		}
	}
	Renderer::Instance()->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	map.Create(o, player->pos, inky->pos, blinky->pos, clyde->pos);
	fruit.Init(player->pos);
	player->SetInitPos();
	inky->SetInitPos();
	blinky->SetInitPos();
	clyde->SetInitPos();

}

void Controller::SceneControl()
{
	// --- GAME LOOP ---
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < DELAY_TIME)
		SDL_Delay((int)(DELAY_TIME - frameTime));
	Renderer::Instance()->Clear();
	frameTimePlayerSprite = 0;

	int pixelsPerFrame = 4;
	switch (state) {
	case SceneState::RUNNING_PLAY:
		keyboard.PollForPlay();
		if (keyboard.keys[SDLK_p] && pAux.running) pAux.paused = true;
		if (keyboard.keys[SDLK_SPACE] && pAux.running) pAux.paused = false;
		if (!pAux.running && keyboard.keys[SDLK_SPACE]) pAux.running = true;
		scene->Update(o, player, clyde, inky, blinky, pAux, keyboard, fruit);
		scene->Draw(o, map, player, clyde, inky, blinky, pAux, keyboard, fruit);

		if (pAux.paused && sound.soundOn && scene->buttons[(int)MENU_SOUND].Used(keyboard)) sound.Stop();
		else if (pAux.paused && !sound.soundOn && scene->buttons[(int)MENU_SOUND].Used(keyboard)) sound.Play();

		//GameOver Provisional ja que no es te el ranking
		if ((player->dead && player->livesLeft <= 0) || player->score >= player->GetMaxScore() || player->score >= MAX_SCORE) {
			ranking.AskPlayerInfo(player->score);
			state = SceneState::GO_TO_RANKING;

		}

		//GoToMenu
		if (pAux.paused && keyboard.keys[SDLK_ESCAPE] || !pAux.running && keyboard.keys[SDLK_ESCAPE]) state = SceneState::GO_TO_MENU;

		break;

	case SceneState::RUNNING_MENU:	//Provisional
		keyboard.GeneralPoll();
		scene->Update(keyboard);
		scene->Draw();

		if (scene->buttons[MENU_PLAY].Used(keyboard)) state = SceneState::GO_TO_PLAY;
		if (scene->buttons[MENU_RANKING].Used(keyboard)) state = SceneState::GO_TO_RANKING;
		if (scene->buttons[MENU_SOUND].Used(keyboard) && sound.soundOn) sound.Stop();
		else if (scene->buttons[MENU_SOUND].Used(keyboard) && !sound.soundOn) sound.Play();
		if (scene->buttons[MENU_EXIT].Used(keyboard)) state = SceneState::GO_TO_EXIT;

		//Aix� al scene->Update()
		//state = SceneState::GO_TO_PLAY;

		break;

	case SceneState::RUNNING_RANKING:
		keyboard.GeneralPoll();
		scene->Update(keyboard);
		scene->Draw(ranking);

		if (scene->buttons[RANKING_EXIT].Used(keyboard)) state = SceneState::GO_TO_MENU;

		break;

	case SceneState::RUNNING_SPLASH_SCREEN:
		//scene = new SplashScreen;
		scene->Draw();
		state = SceneState::GO_TO_MENU;

		break;

	case SceneState::GO_TO_PLAY:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = new Play;
		scene->Load(o, map, player, inky, clyde, blinky, fruit);
		pAux.Reinit();

		state = SceneState::RUNNING_PLAY;
		if (sound.soundOn)
			sound.Play();
		
		break;

	case SceneState::GO_TO_MENU:
		quitSceneTarget = SceneState::GO_TO_EXIT;
		scene = new Menu;

		scene->Load();

		state = SceneState::RUNNING_MENU;

		break;

	case SceneState::GO_TO_RANKING:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = new Ranking;
		scene->Load(ranking);

		state = SceneState::RUNNING_RANKING;

		break;

	case SceneState::GO_TO_EXIT:
		scene = new Exit;

		state = SceneState::EXIT;

		break;

		/*case SceneState::EXIT:	//Crec que no fa falta el case tenint el del GO_TO_EXIT

			break;*/

	default:;

	}

	Renderer::Instance()->Render();
}
