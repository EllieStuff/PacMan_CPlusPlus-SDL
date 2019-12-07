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

#include "Types.h"
#include "Constants.h"
#include "Utils.h"

//Game general information

//TODO: 4, 7, 8, 9, 10 i 11 (2n personatge, col�lisions, elements aleatoris que surtin pel mapa i puntuacions) i arreglar bug de int_char(int num)



int main(int, char*[])
{

	///GameLoop
	Controller controller;
	Renderer *renderer = renderer->Instance();
	Map map;

	std::vector<std::vector<Objects*>> o;
	for (int i = 0; i < MAP_WIDTH + HUD_TILES; i++)
	{
		o.push_back({ new Objects });
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			o[i].push_back({ new Objects });
			o[i][j]->tile = MapTiles::POINTS;
		}
	}
	//map.Create(renderer, o);
	//while (true)
	//{
	//	
	//	map.Draw(renderer, o);
	//}

	Player *player = new Player;
	Clyde *clyde = new Clyde;
	Inky *inky = new Inky;
	map.Create(renderer, o);
	player->LecturaXMLPlayer(renderer);
	clyde->LecturaXMLEnemy(renderer);
	inky->LecturaXMLEnemy(renderer);
	while (controller.state != SceneState::EXIT) {
		renderer->Clear();
		
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
