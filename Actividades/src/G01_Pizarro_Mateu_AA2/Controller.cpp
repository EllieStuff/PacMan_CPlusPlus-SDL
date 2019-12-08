#include "Controller.h"

void Controller::SceneControl(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, Player* player, Clyde* clyde, Inky* inky)
{
	// --- GAME LOOP ---

	bool isClicked = false;
	int pixelsPerFrame = 4;
	Play play;
	SplashScreen ss;
	Exit exit;
	Menu menu;
	Ranking rank;
	Button buttons[(int)ButtonPosition::COUNT];
	HUD hud(renderer, player);
	std::vector<bool> keys(255);
	switch (state) {
	case SceneState::RUNNING_PLAY:
		PollForPlay(keys, isClicked);
		if (keys[SDLK_p]) paused = true;
		if (keys[SDLK_SPACE]) paused = false;
		scene = &play;
		//scene = reinterpret_cast<Play*>(scene);
		//scene->Load(renderer, o, map, player);
		scene->Update(renderer, o, player, clyde, inky, keys, paused, cursor, isClicked, buttons[(int)ButtonPosition::SOUND]);
		scene->Draw(renderer, o, map, hud, player, clyde, inky, paused, cursor, buttons[(int)ButtonPosition::SOUND]);

		if (paused && sound.soundOn && buttons[(int)ButtonPosition::SOUND].Used(cursor, isClicked)) sound.Stop();
		else if (paused && !sound.soundOn && buttons[(int)ButtonPosition::SOUND].Used(cursor, isClicked)) sound.Play();

		//GameOver Provisional ja que no es te el ranking
		if (player->dead || player->score >= map.maxScore) 
			state = SceneState::GO_TO_MENU;

		//GoToMenu
		if (paused && keys[SDLK_ESCAPE]) {
			paused = false;
			state = SceneState::GO_TO_MENU;

		}

		break;

	case SceneState::RUNNING_MENU:	//Provisional
		GeneralPoll(isClicked);
		scene = &menu;
		scene->Update(renderer, buttons, cursor);
		scene->Draw(renderer);

		//Aix� al scene->Update()
		//state = SceneState::GO_TO_PLAY;

		break;

	case SceneState::RUNNING_RANKING:
		GeneralPoll(isClicked);
		scene = &rank;
		/*scene->Update();
		scene->Draw();*/

		break;

	case SceneState::RUNNING_SPLASH_SCREEN:
		scene = &ss;
		/*scene->Update();
		scene->Draw();*/

		//Aix� al scene->Update()
		state = SceneState::GO_TO_MENU;

		break;

	case SceneState::GO_TO_PLAY:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = &play;
		//scene = reinterpret_cast<Play*>(scene);
		scene->Load(renderer, o, map, player, inky, clyde);

		state = SceneState::RUNNING_PLAY;
		if (sound.soundOn)
			sound.Play();
		
		break;

	case SceneState::GO_TO_MENU:
		quitSceneTarget = SceneState::GO_TO_EXIT;
		scene = &menu;

		//scene->Load();

		state = SceneState::RUNNING_MENU;

		break;

	case SceneState::GO_TO_RANKING:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = &rank;
		//scene->Load();

		state = SceneState::RUNNING_RANKING;

		break;

	case SceneState::GO_TO_EXIT:
		scene = &exit;
		//scene->Load();

		state = SceneState::EXIT;

		break;

		/*case SceneState::EXIT:	//Crec que no fa falta el case tenint el del GO_TO_EXIT

			break;*/

	default:;

	}

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
