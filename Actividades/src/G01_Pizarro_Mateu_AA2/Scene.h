#pragma once
#include <Windows.h>

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


class Scene {
protected:
	Color textColor;
	Rect pausedFontStopRect, pausedFontRect1, pausedFontRect2;
	Text pausedFontStopText, pausedFontText1, pausedFontText2;
	Font pausedFontStop, pausedFont1, pausedFont2;
public:

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &);

	virtual void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &,Player*);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &, bool);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, HUD&,Player *, Clyde *, Inky *, bool);

private:


};

class Play : public Scene {
public:
	void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &, bool);
	void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &,Player*);
	void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, HUD&,Player*, Clyde*, Inky*, bool);

};

class Menu : public Scene {
public:
	void Update(Renderer*);
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
	void Update(Renderer*);
	void Draw(Renderer *);

};

class Exit : public Scene {
public:
	void Load(Renderer *);

};