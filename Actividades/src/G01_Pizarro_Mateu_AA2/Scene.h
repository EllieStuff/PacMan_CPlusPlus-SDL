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


class Scene {
public:

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &);

	virtual void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, Player *, Clyde *, Inky *);

private:


};

class Play : public Scene {
public:
	void Update(Renderer *, std::vector<std::vector<Objects*>> &, Player *, Clyde *, Inky *, std::vector<bool> &);
	void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &);
	void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &, Player*, Clyde*, Inky*);

};

class Menu : public Scene {
public:
	void Update();
	void Load(Renderer *);
	void Draw(Renderer *);

};

class Ranking : public Scene {
public:
	void Update();
	void Load(Renderer *);
	void Draw(Renderer *);

};

class SplashScreen : public Scene {
public:
	void Update();
	void Draw(Renderer *);

};

class Exit : public Scene {
public:
	void Load(Renderer *);

};