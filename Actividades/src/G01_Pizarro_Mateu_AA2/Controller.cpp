#include "Controller.h"

void Controller::Update()
{
	//// --- GAME LOOP ---

	////bool isClicked = false;
	////bool isRunning = true;
	//int pixelsPerFrame = 4;
	//while (scene.state != SceneState::EXIT) {
	//	switch (scene.state) {
	//	case SceneState::RUNNING_PLAY:
	//		Poll();

	//		//UPDATE

	//		break;

	//	case SceneState::RUNNING_MENU:	//Provisional
	//		/*Etc...*/

	//		scene.state = SceneState::GO_TO_PLAY;

	//		break;

	//	case SceneState::RUNNING_RANKING:

	//		break;

	//	case SceneState::RUNNING_SPLASH_SCREEN:	//Provisional
	//		Sleep(3);
	//		scene.state = SceneState::GO_TO_MENU;

	//		break;

	//	case SceneState::GO_TO_PLAY:
	//		/*Etc...*/

	//		scene.state = SceneState::RUNNING_PLAY;

	//		break;

	//	case SceneState::GO_TO_MENU:	//Provisional
	//		/*Etc...*/

	//		scene.state = SceneState::RUNNING_MENU;

	//		break;

	//	case SceneState::GO_TO_RANKING:

	//		break;

	//	case SceneState::GO_TO_EXIT:

	//		break;

	//		/*case SceneState::EXIT:	//Crec que no fa falta el case tenint el del GO_TO_EXIT

	//			break;*/

	//	default:;

	//	}

	//}

}

void Controller::Poll()
{
	//SDL_Event event;
	//std::vector<bool> keys(255);
	//// HANDLE EVENTS
	//while (SDL_PollEvent(&event)) {
	//	switch (event.type) {
	//	case SDL_QUIT:
	//		scene.state = SceneState::EXIT;
	//		break;
	//	case SDL_KEYDOWN:
	//		keys[event.key.keysym.sym] = true;
	//		break;
	//	case SDL_KEYUP:
	//		keys[event.key.keysym.sym] = false;
	//		break;
	//	case SDL_MOUSEMOTION:
	//		cursor.x = event.motion.x;
	//		cursor.y = event.motion.y;
	//		break;
	//	case SDL_MOUSEBUTTONDOWN:
	//		//isClicked = true;
	//	default:;
	//	}
	//}

}
