#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

#include "Constants.h"
#include "Utils.h"
#include "Types.h"
#include "Renderer.h"


struct PlayerData {
	std::string name = "";
	int score = 0;


	PlayerData() {};
	PlayerData(const PlayerData &p) : name(p.name), score(p.score) {};
	PlayerData(const std::string &_name, const int &_score) : name(_name), score(_score) {};

};


class RankingData {
private:
	Font font;
	Color textColor;
	Text texts[RANKING_CAPACITY];
	Rect rects[RANKING_CAPACITY];

	void AddPlayer(const PlayerData &newPlayer);
	void Save();
	void Recover();

public:
	std::vector<PlayerData> players;
	std::string fileName = "ranking.bin";

	RankingData();

	void AskPlayerInfo(const int &pScore);
	void Draw();
	void Update();
	void Load();

};