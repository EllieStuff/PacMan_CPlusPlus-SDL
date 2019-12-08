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

//Game general information


int main(int, char*[])
{

	///GameLoop
	Controller controller;
	Renderer *renderer = renderer->Instance();
	Map map;
	Uint32 frameStart, frameTime;
	std::vector<std::vector<Objects*>> o;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		o.push_back({ new Objects });
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			o[i].push_back({ new Objects });
			o[i][j]->tile = MapTiles::POINTS;
		}
	}
	renderer->LoadTexture("PacmanSheet", "../../res/img/PacManSpritesheet.png");
	int frameWidth = renderer->GetTextureSize("PacmanSheet").x / 8;
	int frameHeight = renderer->GetTextureSize("PacmanSheet").y / 8;
	int frameTimePlayerSprite = 0;
	Player *player = new Player;
	Clyde *clyde = new Clyde;
	Inky *inky = new Inky;
	HUD hud(renderer, player);
	map.Create(renderer, o);
	player->LecturaXMLPlayer(renderer);
	clyde->LecturaXMLEnemy(renderer);
	inky->LecturaXMLEnemy(renderer);


	while (controller.state != SceneState::EXIT) {
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));

		renderer->Clear();
		frameTimePlayerSprite = 0;
		controller.SceneControl(renderer, o, map, player, clyde, inky);
		renderer->Render();

	}


	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	return 0;
}
