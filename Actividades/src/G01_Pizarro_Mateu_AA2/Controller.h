#pragma once
#include <Windows.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Scene.h"

class Controller {
public:
	Rect cursor;
	Scene *scene = new Scene;
	SceneState quitSceneTarget = SceneState::GO_TO_EXIT;

	Controller() {
		scene = reinterpret_cast<SplashScreen*>(scene); //TODO: Fer els cast en els GO_TO del Controller

	}

	void SceneControl();

private:
	void PollForPlay();

	void GeneralPoll();

};