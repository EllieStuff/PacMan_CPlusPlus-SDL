#pragma once
#include <Windows.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"


class Scene {
public:
	SceneState state = SceneState::RUNNING_SPLASH_SCREEN;

	virtual void Update();

	virtual void Load();

	virtual void Draw();

private:


};

class Play : public Scene {
public:
	void Update();
	void Load();
	void Draw();

};

class Menu : public Scene {
public:
	void Update();
	void Load();
	void Draw();

};

class Ranking : public Scene {
public:
	void Update();
	void Load();
	void Draw();

};

class SplashScreen : public Scene {
public:
	void Update();
	void Draw();

};

class Exit : public Scene {
public:
	void Load();

};