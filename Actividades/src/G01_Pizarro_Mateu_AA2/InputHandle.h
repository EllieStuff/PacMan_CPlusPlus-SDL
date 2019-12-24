#pragma once
#include <vector>
#include <Windows.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
//#include "Scene.h"

class InputHandle {
public:
	std::vector<bool> keys;
	bool isClicked = false;
	Rect cursor;
	//SDL_Event event;

	InputHandle();
	void PollForPlay();
	void GeneralPoll();

private:
	void ResetKeys();

};