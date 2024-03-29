#include "Sound.h"

Sound::Sound()
{
	soundtrack = { Mix_LoadMUS("../../res/au/pacman-waka-waka.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
}

void Sound::Play()
{
	Mix_PlayMusic(soundtrack, -1);
	soundOn = true;
}

void Sound::Stop()
{
	Mix_PauseMusic();
	soundOn = false;
}

void Sound::Update()
{
}