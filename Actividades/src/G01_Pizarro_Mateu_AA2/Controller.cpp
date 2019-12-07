#include "Controller.h"

void Controller::SceneControl(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map, Player* player, Clyde* clyde, Inky* inky)
{
	// --- GAME LOOP ---

	//bool isClicked = false;
	//bool isRunning = true;
	int pixelsPerFrame = 4;
	Play play;
	SplashScreen ss;
	Exit exit;
	Menu menu;
	Ranking rank;
	std::vector<bool> keys(255);
	switch (state) {
	case SceneState::RUNNING_PLAY:
		PollForPlay(keys);
		scene = &play;
		//scene = reinterpret_cast<Play*>(scene);
		scene->Load(renderer, o, map);
		scene->Update(renderer, o, player, clyde, inky, keys);
		scene->Draw(renderer, o, map, player, clyde, inky);

		break;

	case SceneState::RUNNING_MENU:	//Provisional
		GeneralPoll();
		scene = &menu;
		//scene->Update();
		//scene->Draw();

		//Això al scene->Update()
		state = SceneState::GO_TO_PLAY;

		break;

	case SceneState::RUNNING_RANKING:
		GeneralPoll();
		scene = &rank;
		/*scene->Update();
		scene->Draw();*/

		break;

	case SceneState::RUNNING_SPLASH_SCREEN:
		scene = &ss;
		/*scene->Update();
		scene->Draw();*/

		//Això al scene->Update()
		state = SceneState::GO_TO_MENU;

		break;

	case SceneState::GO_TO_PLAY:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = &play;
		//scene = reinterpret_cast<Play*>(scene);
		scene->Load(renderer, o, map);

		state = SceneState::RUNNING_PLAY;

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

void Controller::PollForPlay(std::vector<bool> &keys)
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
			//isClicked = true;
		default:;
		}
	}

}

void Controller::GeneralPoll()
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
			//isClicked = true;
		default:;
		}
	}

}
