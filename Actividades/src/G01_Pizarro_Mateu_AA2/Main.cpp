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

	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- INIT SDL_ttf ---
	if (TTF_Init()) throw "No es pot inicialitzar SDL_ttf";

	// --- INIT SDL_mixer ---
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)&mixFlags)) throw "No es pot inicialitzar SDL_mixer";


	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";


	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 60;
	float deltaTime = 1000.0f;
	Uint32 frameStart, frameTime;


	// --- SPRITES ---
		//SpriteSheet
	SDL_Texture* spritesTexture{ IMG_LoadTexture(m_renderer, "../../res/img/PacManSpritesheet.png") };
	if (spritesTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


	////Cursor
	////Rect cursorRect{ 0, 0, 100, 50 };
	//Vector2 cursorTarget(20, 20);


	////-->Animated Sprite ---
	//SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/PacManSpritesheet.png") };
	//SDL_Rect playerRect, playerPosition;
	//int textWidth, textHeight, frameWidth, frameHeight;
	//SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	//frameWidth = textWidth / 6;
	//frameHeight = textHeight / 1;
	//playerPosition.x = playerPosition.y = 0;
	//playerRect.x = playerRect.y = 0;
	//playerPosition.h = playerRect.h = frameHeight;
	//playerPosition.w = playerRect.w = frameWidth;
	//int frameTimePlayerSprite = 0;
	Map map;
	map.Create();
	

	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	return 0;
}
