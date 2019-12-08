#pragma once
#include <Windows.h>
#include <ctime>

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
#include "HUD.h"
#include "Button.h"


class Scene {
protected:
	Color textColor;
	Rect pausedFontStopRect, pausedFontRect1, pausedFontRect2;
	Text pausedFontStopText, pausedFontText1, pausedFontText2;
	Font pausedFontStop, pausedFont1, pausedFont2;
	clock_t begin, end;
	

public:
	Button *buttons = new Button[(int)ButtonPosition::COUNT];
	double elapsed_secs;
	Scene();

	virtual void Update(Renderer *);

	virtual void Load(Renderer *);

	virtual void Draw(Renderer *);

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &, bool, Rect &, bool &);

	virtual void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &, Player*, Inky *, Clyde *);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, HUD&,Player *, Clyde *, Inky *, bool, Rect &);

	virtual void Update(Renderer *, Rect &);

private:


};

class Play : public Scene {
public:
	void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &, bool, Rect &, bool &);
	void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &,Player*, Inky *, Clyde *);
	void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, HUD&,Player*, Clyde*, Inky*, bool, Rect &);

};

class Menu : public Scene {
public:
	void Update(Renderer*, Rect &);
	void Load(Renderer *);
	void Draw(Renderer *);

};

class Ranking : public Scene {
public:
	void Update(Renderer*);
	void Load(Renderer *);
	void Draw(Renderer *);

};

class SplashScreen : public Scene {
public:
	void Update(Renderer * renderer);
	void Draw(Renderer *);

};

class Exit : public Scene {
public:
	void Load(Renderer *);

};