#include "InputHandle.h"

InputHandle::InputHandle()
{
	keys = std::vector<bool>(255);
}

void InputHandle::PollForPlay()
{
	// HANDLE EVENTS
	SDL_Event event;
	ResetKeys();
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
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
			isClicked = true;
		default:;
		}
	}

}

void InputHandle::GeneralPoll()
{
	// HANDLE EVENTS
	SDL_Event event;
	ResetKeys();
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			break;
		case SDL_MOUSEMOTION:
			cursor.x = event.motion.x;
			cursor.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			isClicked = true;
		default:;
		}
	}
}

void InputHandle::ResetKeys()
{
	isClicked = false;
	for (std::vector<bool>::iterator it = keys.begin(); it != keys.end(); it++)
		*it = false;

}
