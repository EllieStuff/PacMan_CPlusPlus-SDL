#include "Controller.h"

void Controller::SceneControl()
{
	// --- GAME LOOP ---

	//bool isClicked = false;
	//bool isRunning = true;
	int pixelsPerFrame = 4;
	switch (scene->state) {
	case SceneState::RUNNING_PLAY:
		PollForPlay();
		scene = reinterpret_cast<Play*>(scene);
		scene->Update();
		scene->Draw();

		break;

	case SceneState::RUNNING_MENU:	//Provisional
		GeneralPoll();
		scene = reinterpret_cast<Menu*>(scene);
		scene->Update();
		scene->Draw();

		//Aix� al scene->Update()
		//scene->state = SceneState::GO_TO_PLAY;

		break;

	case SceneState::RUNNING_RANKING:
		GeneralPoll();
		scene = reinterpret_cast<Ranking*>(scene);
		scene->Update();
		scene->Draw();

		break;

	case SceneState::RUNNING_SPLASH_SCREEN:
		scene = reinterpret_cast<SplashScreen*>(scene);
		scene->Update();
		scene->Draw();

		//Aix� al scene->Update()
		//scene->state = SceneState::GO_TO_MENU;

		break;

	case SceneState::GO_TO_PLAY:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = reinterpret_cast<Play*>(scene);
		scene->Load();

		scene->state = SceneState::RUNNING_PLAY;

		break;

	case SceneState::GO_TO_MENU:
		quitSceneTarget = SceneState::GO_TO_EXIT;
		scene = reinterpret_cast<Menu*>(scene);
		scene->Load();

		scene->state = SceneState::RUNNING_MENU;

		break;

	case SceneState::GO_TO_RANKING:
		quitSceneTarget = SceneState::GO_TO_MENU;
		scene = reinterpret_cast<Ranking*>(scene);
		scene->Load();

		scene->state = SceneState::RUNNING_RANKING;

		break;

	case SceneState::GO_TO_EXIT:
		scene = reinterpret_cast<Exit*>(scene);
		scene->Load();

		scene->state = SceneState::EXIT;

		break;

		/*case SceneState::EXIT:	//Crec que no fa falta el case tenint el del GO_TO_EXIT

			break;*/

	default:;

	}

}

void Controller::PollForPlay()
{
	SDL_Event event;
	std::vector<bool> keys(255);
	// HANDLE EVENTS
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			scene->state = quitSceneTarget;
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
			scene->state = quitSceneTarget;
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
