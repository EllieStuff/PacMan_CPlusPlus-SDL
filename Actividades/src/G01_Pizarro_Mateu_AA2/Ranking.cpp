#include "Ranking.h"

void RankingData::AddPlayer(const PlayerData &newPlayer)
{
	if (players.empty() || players.size() < RANKING_CAPACITY && newPlayer.score < players[players.size() - 1].score) {
		players.push_back(newPlayer);
		Save();
		return;

	}

	for (std::vector<PlayerData>::iterator it = players.begin(); it != players.end(); it++) {
		if (newPlayer.score >= it->score) {
			players.insert(it, newPlayer);
			if (players.size() > RANKING_CAPACITY) players.resize(RANKING_CAPACITY);
			Save();

			break;
		}

	}

}

RankingData::RankingData()
{
	Recover();

	textColor.Init(255, 255, 255, 255);
	font.Init("GameplayFont", "../../res/ttf/Gameplay.ttf", 80);
	Renderer::Instance()->LoadFont(font);

	//scoreText.Init(font.id, Utils::AddZerosInFrontOfStr(player->score, 4), textColor);
	//score.Init(SCREEN_WIDTH - HUD_WIDTH + HUD_EDGES, HUD_EDGES * 3, 160, 80);

	for (int i = 0; i < RANKING_CAPACITY; i++) {
		//Aixo seria millor fer-ho amb rects pels nmos i per les scores per separat, pero de moment mirem que tot funcioni be
		rects[i].Init(RANKING_EDGES, i * (50 + RANKING_EDGES) + RANKING_EDGES, 600, 50);

	}

}

void RankingData::AskPlayerInfo(const int &pScore)
{
	PlayerData pData;
	pData.score = pScore;
	std::cout << "\nGAME OVER\n\nCongrats! You got " << pScore << " points.\nWhat's your name? ";
	std::cin >> pData.name;

	AddPlayer(pData);

}

void RankingData::Draw()
{
	//std::cout << "\n\nRANKING\n";
	for (int i = 0; i < players.size(); i++) {
		//std::cout << players[i].name << "	" << players[i].score << std::endl;
		Renderer::Instance()->PushImage(texts[i].id, Utils::RectToSDL_Rect(rects[i]));

	}

}

void RankingData::Update()
{
	

}

void RankingData::Load()
{
	for (int i = 0; i < players.size(); i++) {
		std::string newId = "ranking";
		newId += static_cast<char>(i);
		texts[i].Init(newId, players[i].name + " - " + Utils::AddZerosInFrontOfStr(players[i].score, 4), textColor);
		Renderer::Instance()->LoadTextureText(font.id, texts[i]);

	}

}

void RankingData::Save()
{
	size_t len = players.size();
	PlayerData *tmp = new PlayerData[len];
	std::ofstream fSalida(fileName, std::ios::out | std::ios::binary);
	fSalida.write(reinterpret_cast<char *>(&len), sizeof(size_t));
	for (int i = 0; i < len; i++)
	{
		tmp[i] = players[i];
	}
	fSalida.write(reinterpret_cast<char *>(tmp), sizeof(PlayerData)*len);

	delete[]tmp;
	fSalida.close();

}

void RankingData::Recover()
{
	//TODO: Veure prq ja no llegeix el ranking amb mes de 5 players
	size_t len;
	std::ifstream fEntrada(fileName, std::ios::in | std::ios::binary);
	fEntrada.read(reinterpret_cast<char *>(&len), sizeof(size_t));
	if (len > 0) {
		players.resize(len);
		PlayerData *tmp = new PlayerData[len];
		fEntrada.read(reinterpret_cast<char *>(tmp), sizeof(PlayerData) *len);
		for (int i = 0; i < len; i++)
		{
			players[i] = tmp[i];
		}

		//delete[]tmp;
		fEntrada.close();

	}

}
