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
	bool paused = false;

	Controller() {
		state = SceneState::RUNNING_SPLASH_SCREEN;

	}

	void SceneControl(Renderer *, std::vector<std::vector<Objects*>> &, Map &, Player*, Clyde*, Inky*);

private:
	void PollForPlay(std::vector<bool> &);

	void GeneralPoll();

};