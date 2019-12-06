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

//#include "Scene.h"
//#include "Controller.h"
//#include "Characters.h"	//Ha de ser el pare dels Enemies i del Player
#include "Map.h"

#include "Types.h"
#include "Constants.h"
#include "Utils.h"

//Game general information

//TODO: 4, 7, 8, 9, 10 i 11 (2n personatge, col·lisions, elements aleatoris que surtin pel mapa i puntuacions) i arreglar bug de int_char(int num)


int main(int, char*[])
{

	

	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 60;
	float deltaTime = 1000.0f;
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
	Renderer *renderer = renderer->Instance();
	while (true)
	{
		Map map;
		map.Create(renderer, o);
		//map.Draw(renderer, o);
	}
	

	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	return 0;
}
