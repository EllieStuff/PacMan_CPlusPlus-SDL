#include "Scene.h"

void Scene::Update(){}

void Scene::Load(){}

void Scene::Draw(){}

void SplashScreen::Update()	//Nota: Es provisional, currar-s'ho una miqueta plis xD
{
	Sleep(3);

	state = SceneState::GO_TO_MENU;
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

void Play::Update()
{
	/*Whatever that goes here*/
	//Moure Player
	//Moure Enemics
	//Recollir power ups i punts

}

void Play::Load()
{


}

void Play::Draw()
{


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
