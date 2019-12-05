#pragma once
#include <Windows.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Scene.h"

class Controller {
public:
	Rect cursor;
	Scene scene;

	void Update();

private:
	void Poll();

};