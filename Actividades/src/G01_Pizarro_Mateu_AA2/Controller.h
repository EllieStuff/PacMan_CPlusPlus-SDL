#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Scene.h"
#include "Map.h"

class Controller {
public:
	Rect cursor;
	Scene *scene = new Scene;
	SceneState state;
	SceneState quitSceneTarget = SceneState::GO_TO_EXIT;

	Controller() {
		state = SceneState::RUNNING_SPLASH_SCREEN;

	}

	void SceneControl(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

private:
	void PollForPlay();

	void GeneralPoll();

};