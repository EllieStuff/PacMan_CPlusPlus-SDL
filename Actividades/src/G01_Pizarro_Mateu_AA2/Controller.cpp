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

	bool isClicked = false;
	int pixelsPerFrame = 4;
	std::vector<bool> keys(255);
	switch (state) {
	case SceneState::RUNNING_PLAY:
		PollForPlay(keys, isClicked);
		if (keys[SDLK_p] && running) paused = true;
		if (keys[SDLK_SPACE] && running) paused = false;
		if (!running && keys[SDLK_SPACE]) running = true;
		scene->Update(o, player, clyde, inky, blinky, keys, paused, running, cursor, isClicked);
		scene->Draw(o, map, player, clyde, inky, blinky, paused, running, cursor);

		if (paused && sound.soundOn && scene->buttons[(int)MENU_SOUND].Used(cursor, isClicked)) sound.Stop();
		else if (paused && !sound.soundOn && scene->buttons[(int)MENU_SOUND].Used(cursor, isClicked)) sound.Play();

		//GameOver Provisional ja que no es te el ranking
		if ((player->dead && player->livesLeft <= 0) || player->score >= map.maxScore) 
			state = SceneState::GO_TO_MENU;

		//GoToMenu
		if (paused && keys[SDLK_ESCAPE] || !running && keys[SDLK_ESCAPE]) state = SceneState::GO_TO_MENU;

		break;

	case SceneState::RUNNING_MENU:	//Provisional
		GeneralPoll(isClicked);
		scene->Update(cursor);
		scene->Draw();

		if (scene->buttons[MENU_PLAY].Used(cursor, isClicked)) state = SceneState::GO_TO_PLAY;
		//if (scene->buttons[MENU_RANKING].Used(cursor, isClicked)) state = SceneState::GO_TO_RANKING;	//Silenciat prq el ranking encara no hi es
		if (scene->buttons[MENU_SOUND].Used(cursor, isClicked) && sound.soundOn) sound.Stop();
		else if (scene->buttons[MENU_SOUND].Used(cursor, isClicked) && !sound.soundOn) sound.Play();
		if (scene->buttons[MENU_EXIT].Used(cursor, isClicked)) state = SceneState::GO_TO_EXIT;

		//Aix� al scene->Update()
		//state = SceneState::GO_TO_PLAY;

		break;

	case SceneState::RUNNING_RANKING:
		GeneralPoll(isClicked);

		break;

	case SceneState::RUNNING_SPLASH_SCREEN:
		//scene = new SplashScreen;
		scene->Draw();
		state = SceneState::GO_TO_MENU;

		break;

	case SceneState::GO_TO_PLAY:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = new Play;
		scene->Load(o, map, player, inky, clyde, blinky);
		running = false;
		paused = false;

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

void Controller::PollForPlay(std::vector<bool> &keys, bool &isClicked)
{
	SDL_Event event;

	// HANDLE EVENTS
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			state = quitSceneTarget;
			break;
		case SDL_KEYDOWN:
			keys[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = false;
			break;
		case SDL_MOUSEMOTION:
			cursor.x = event.motion.x;
			cursor.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			isClicked = true;
		default:;
		}
	}

}

void Controller::GeneralPoll(bool &isClicked)
{
	SDL_Event event;
	// HANDLE EVENTS
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			state = quitSceneTarget;
			break;
		case SDL_MOUSEMOTION:
			cursor.x = event.motion.x;
			cursor.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			isClicked = true;
		default:;
		}
	}

}
