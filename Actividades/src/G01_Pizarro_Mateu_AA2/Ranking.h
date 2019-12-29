#pragma once

#include <vector>
#include <iostream>
#include <fstream>

struct Player {
	std::string name = "";
	int score = 0;

	Player() {};
	Player(Player &p) : name(p.name), score(p.score) {};
	Player(const std::string &_name, const int &_score) : name(_name), score(_score) {};

};


class Ranking {
	std::vector<Player> players;


};