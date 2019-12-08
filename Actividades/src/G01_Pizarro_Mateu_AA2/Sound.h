#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class Sound
{
public:
	bool soundOn = false;
	Mix_Music *soundtrack; 
	//Constructor
	Sound();
	//Functions
	void Update();
	void Stop();
	void Play();
};