#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class Sound
{
public:
	bool soundOn = false;

	Mix_Music *soundtrack; 
	Sound();
	void Update();
	void Stop();
	void Play();
};