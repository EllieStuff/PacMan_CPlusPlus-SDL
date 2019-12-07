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

//TODO: 4, 7, 8, 9, 10 i 11 (2n personatge, col�lisions, elements aleatoris que surtin pel mapa i puntuacions) i arreglar bug de int_char(int num)



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
	//map.Create(renderer, o);
	//while (true)
	//{
	//	
	//	map.Draw(renderer, o);
	//}
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




	frameStart = SDL_GetTicks();
	while (controller.state != SceneState::EXIT) {

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
		#pragma region ANIMACIONES
		frameTimePlayerSprite++;
		if (FPS / frameTimePlayerSprite <= 9) {
			if (player->dir == Direction::NONE ||player->dir == Direction::RIGHT)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if ((player->rect.x >= frameWidth * 6) || (clyde->rect.x >= frameWidth * 8) 
					|| (inky->rect.x >= frameWidth * 6))
				{
					player->rect.x = 4 * frameWidth;
					clyde->rect.x = 6 * frameWidth;
					inky->rect.x = 4 * frameWidth;
				}
			}
			if (player->dir == Direction::LEFT)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 8 || (clyde->rect.x >= frameWidth * 6)
					|| (inky->rect.x >= frameWidth * 8))
				{
					player->rect.x = 6 * frameWidth;
					clyde->rect.x = 4 * frameWidth;
					inky->rect.x = 6 * frameWidth;
				}
			}
			if (player->dir == Direction::UP)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 2 || (clyde->rect.x >= frameWidth * 4)
					|| (inky->rect.x >= frameWidth * 2))
				{
					player->rect.x = 0;
					clyde->rect.x = 2 * frameWidth;
					inky->rect.x = 0;
				}
			}
			if (player->dir == Direction::DOWN)
			{
				player->rect.x += frameWidth;
				clyde->rect.x += frameWidth;
				inky->rect.x += frameWidth;
				if (player->rect.x >= frameWidth * 4 || (clyde->rect.x >= frameWidth * 2)
					|| (inky->rect.x >= frameWidth * 4))
				{
					player->rect.x = 2 * frameWidth;
					clyde->rect.x = 0;
					inky->rect.x = 2 * frameWidth;
				}
			}
		#pragma endregion
			renderer->Clear();
			frameTimePlayerSprite = 0;
			controller.SceneControl(renderer, o, map, player, clyde, inky);
			hud.Update(renderer, player);
			hud.Draw(renderer, player);

			renderer->Render();

			/*if (playerRect.x >= textWidth)
				playerRect.x = 0;*/

		}
		//controller.SceneControl(renderer, o, map, player, clyde, inky);
		frameStart = SDL_GetTicks();
	}


	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	return 0;
}
