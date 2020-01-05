#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "Controller.h"
#include "Character.h"
#include "Player.h"
#include "Enemies.h"
#include "Clyde.h"
#include "Inky.h"
#include "HUD.h"

#include "Types.h"
#include "Constants.h"
#include "Utils.h"



int main(int, char*[])
{
	srand(time(NULL));

	///GameLoop
	Controller controller;

	while (controller.state != SceneState::EXIT) {
		controller.SceneControl();

	}


	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	return 0;
}
