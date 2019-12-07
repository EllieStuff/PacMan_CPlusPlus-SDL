#pragma once
#include <Windows.h>

#include "Constants.h"
#include "Types.h"
#include "Utils.h"
#include "Map.h"
#include "Renderer.h"


class Scene {
public:

	virtual void Update(Renderer *, std::vector<std::vector<Objects*>> &);

	virtual void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

	virtual void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

private:


};

class Play : public Scene {
public:
	void Update(Renderer *, std::vector<std::vector<Objects*>> &);
	void Load(Renderer *, std::vector<std::vector<Objects*>> &, Map &);
	void Draw(Renderer *, std::vector<std::vector<Objects*>> &, Map &);

};

class Menu : public Scene {
public:
	void Update();
	void Load();
	void Draw();

};

class Ranking : public Scene {
public:
	void Update();
	void Load();
	void Draw();

};

class SplashScreen : public Scene {
public:
	void Update();
	void Draw();

};

class Exit : public Scene {
public:
	void Load();

};