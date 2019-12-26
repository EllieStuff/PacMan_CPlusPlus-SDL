#pragma once
//#include <Windows.h>
#include <time.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Map.h"
#include "Renderer.h"
#include "Character.h"
#include "Player.h"
#include "Enemies.h"
#include "Inky.h"
#include "Clyde.h"
#include "Blinky.h"
#include "Fruit.h"
#include "HUD.h"
#include "Button.h"
#include "InputHandle.h"

struct PlayAuxiliars {
	bool paused = false;
	bool running = false;
	bool timeDifChecked = false;
	long long powerUpTDif = 0;

	PlayAuxiliars() {};
	void Reinit() {
		paused = false;
		running = false;
		powerUpTDif = 0;

	}

};

class Scene {
protected:
	Color textColor;
	Rect notRunningRect1, notRunningRect2, pausedFontStopRect, pausedFontRect1, pausedFontRect2;
	Text notRunningText1, notRunningText2, pausedFontStopText, pausedFontText1, pausedFontText2;
	Font notRunningFont1, notRunningFont2, pausedFontStop, pausedFont1, pausedFont2;
public:
	Button *buttons = new Button[(int)ButtonPosition::COUNT];
	//Constructor
	Scene();
	//Functions
	virtual void Update();
	virtual void Load();
	virtual void Draw();
	virtual void Update(std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &);
	virtual void Load(std::vector<std::vector<Objects*>> &, Map &, Player*, Inky *, Clyde *, Blinky *, Fruit &);
	virtual void Draw(std::vector<std::vector<Objects*>> &, Map &, Player *, Clyde *, Inky *, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &);
	virtual void Update(InputHandle &);
};

class Play : public Scene {
public:
	//Functions
	void Update(std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &);
	void Load(std::vector<std::vector<Objects*>> &, Map &,Player*, Inky *, Clyde *, Blinky *, Fruit &);
	void Draw(std::vector<std::vector<Objects*>> &, Map &, Player*, Clyde*, Inky*, Blinky *, PlayAuxiliars &, InputHandle &, Fruit &);

};

class Menu : public Scene {
public:
	//Functions
	void Update(InputHandle &);
	void Load();
	void Draw();
};

class Ranking : public Scene {
public:
	//Functions
	void Update();
	void Load();
	void Draw();
};

class SplashScreen : public Scene {
public:
	//Functions
	void Update();
	void Draw();
};

class Exit : public Scene {
public:
	//Functions
	void Load();
};