#include "Scene.h"

void Scene::Update(Renderer *, std::vector<std::vector<Objects*>> &) {}

void Scene::Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &) {}

void Scene::Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &) {}

void SplashScreen::Update()	//Nota: Es provisional, currar-s'ho una miqueta plis xD
{
	Sleep(3);

	//state = SceneState::GO_TO_MENU;
}

void SplashScreen::Draw(Renderer *renderer)
{
	//renderer->PushSprite("PacmanSheet", Utils::RectToSDL_Rect(_o[i][j]->rect), RectToSDL_Rect(_o[i][j]->rectPos));

}

void Menu::Update()
{
	/*if () state = SceneState::GO_TO_PLAY;
	else if () state = SceneState::GO_TO_MENU;
	else if () state = SceneState::GO_TO_RANKING;*/

}

void Menu::Load(Renderer *renderer)
{


}

void Menu::Draw(Renderer *renderer)
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

void Ranking::Load(Renderer *renderer)
{


}

void Ranking::Draw(Renderer *renderer)
{


}

void Exit::Load(Renderer *renderer)
{


}
