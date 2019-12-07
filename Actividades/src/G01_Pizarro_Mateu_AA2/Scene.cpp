#include "Scene.h"

void Scene::Update(Renderer *, std::vector<std::vector<Objects*>> &){}

void Scene::Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &){}

void Scene::Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &){}

void SplashScreen::Update()	//Nota: Es provisional, currar-s'ho una miqueta plis xD
{
	//Sleep(4);

	//state = SceneState::GO_TO_MENU;
}

void SplashScreen::Draw()
{


}

void Menu::Update()
{
	/*if () state = SceneState::GO_TO_PLAY;
	else if () state = SceneState::GO_TO_MENU;
	else if () state = SceneState::GO_TO_RANKING;*/

}

void Menu::Load()
{


}

void Menu::Draw()
{


}

void Play::Update(Renderer *renderer, std::vector<std::vector<Objects*>> &o)
{
	/*Whatever that goes here*/
	//Moure Player
	//Moure Enemics
	//Recollir power ups i punts

}

void Play::Load(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map)
{
	map.Create(renderer, o);

	//Posar enemies i player

}

void Play::Draw(Renderer *renderer, std::vector<std::vector<Objects*>> &o, Map &map)
{
	//map.PrintTablero(renderer, o);
	map.Draw(renderer, o);

}

void Ranking::Update()
{
	//Necessitem un Update del ranking?

}

void Ranking::Load()
{


}

void Ranking::Draw()
{


}

void Exit::Load()
{


}
