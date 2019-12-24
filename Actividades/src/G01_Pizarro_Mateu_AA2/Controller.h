#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Scene.h"
#include "Map.h"
#include "Sound.h"
#include "InputHandle.h"

class Controller {
private:
	bool changeSceneType = true;
	bool paused = false;
	bool running = false;
public:
	InputHandle keyboard;
	Scene *scene = new Scene;
	SceneState state = SceneState::RUNNING_SPLASH_SCREEN;
	SceneState quitSceneTarget = SceneState::GO_TO_EXIT;
	Sound sound;
	Uint32 frameStart, frameTime;
	int frameTimePlayerSprite = 0;
	Map map;
	std::vector<std::vector<Objects*>> o;
	Player *player = new Player;
	Clyde *clyde = new Clyde;
	Inky *inky = new Inky;
	Blinky *blinky = new Blinky;
	//Constructor
	Controller();
	//Functions
	void SceneControl();
};