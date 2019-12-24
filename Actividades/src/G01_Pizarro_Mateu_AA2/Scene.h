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
#include "HUD.h"
#include "Button.h"
#include "InputHandle.h"


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
	virtual void Update(std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, Blinky *, bool, bool, InputHandle &);
	virtual void Load(std::vector<std::vector<Objects*>> &, Map &, Player*, Inky *, Clyde *, Blinky *);
	virtual void Draw(std::vector<std::vector<Objects*>> &, Map &, Player *, Clyde *, Inky *, Blinky *, bool, bool, InputHandle &);
	virtual void Update(InputHandle &);
};

class Play : public Scene {
public:
	//Functions
	void Update(std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, Blinky *, bool, bool, InputHandle &);
	void Load(std::vector<std::vector<Objects*>> &, Map &,Player*, Inky *, Clyde *, Blinky *);
	void Draw(std::vector<std::vector<Objects*>> &, Map &, Player*, Clyde*, Inky*, Blinky *, bool, bool, InputHandle &);

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