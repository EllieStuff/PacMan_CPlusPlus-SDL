#pragma once
#include "Constants.h"
#include "Types.h"
#include "Utils.h"


class Scene {
public:
	SceneState state = SceneState::RUNNING_SPLASH_SCREEN;

	void Update();

	virtual void Draw();

private:


};