#include "Ranking.h"

void RankingData::AddPlayer(const PlayerData &newPlayer)
{
	if (players.empty() || players.size() < RANKING_CAPACITY && newPlayer.score < players[players.size() - 1].score) {
		players.push_back(newPlayer);
		InitRects();
		Save();
		return;

	}

	for (std::vector<PlayerData>::iterator it = players.begin(); it != players.end(); it++) {
		if (newPlayer.score >= it->score) {
			players.insert(it, newPlayer);
			if (players.size() > RANKING_CAPACITY) players.resize(RANKING_CAPACITY);
			InitRects();
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


	InitRects();

}

void RankingData::AskPlayerInfo(const int &pScore)
{
	PlayerData pData;
	pData.score = pScore;
	std::cout << "\nGAME OVER\n\nCongrats! You got " << pScore << " points.\nWhat's your name? ";
	std::cin >> pData.name;
	while (pData.name.length() >= NAME_MAX_SIZE) {
		std::cout << "\n\nSORRY! Your name must have less than " << NAME_MAX_SIZE << " characters! Try again, you troll.\n";
		std::cin >> pData.name;

	}


	AddPlayer(pData);

}

void RankingData::Draw()
{
	Renderer::Instance()->PushImage(rankingText.id, Utils::RectToSDL_Rect(rankingRect));
	for (int i = 0; i < players.size(); i++) {
		Renderer::Instance()->PushImage(numTexts[i].id, Utils::RectToSDL_Rect(numRects[i]));
		Renderer::Instance()->PushImage(nameTexts[i].id, Utils::RectToSDL_Rect(nameRects[i]));
		Renderer::Instance()->PushImage(scoreTexts[i].id, Utils::RectToSDL_Rect(scoreRects[i]));

	}

}

void RankingData::Update()
{
	

}

void RankingData::Load()
{
	rankingText.Init("RankingText", "Ranking", textColor);
	Renderer::Instance()->LoadTextureText(font.id, rankingText);
	for (int i = 0; i < players.size(); i++) {
		char pos = i + '1';
		//std::string num = pos + ". ";
		std::string numsId = "";
		numsId += pos;
		numsId += ". ";
		std::string scoresId = "RankedScores";
		scoresId += pos;
		std::string namesId = "RankedNames";
		namesId += pos;
		//newId += static_cast<char>(i);
		numTexts[i].Init(numsId, numsId, textColor);
		nameTexts[i].Init(scoresId, players[i].name, textColor);
		scoreTexts[i].Init(namesId, " - " + Utils::AddZerosInFrontOfStr(players[i].score, 4), textColor);


		Renderer::Instance()->LoadTextureText(font.id, numTexts[i]);
		Renderer::Instance()->LoadTextureText(font.id, nameTexts[i]);
		Renderer::Instance()->LoadTextureText(font.id, scoreTexts[i]);

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
	//Save();	//Pa borrar el ranking
	size_t len;
	std::ifstream fEntrada(fileName, std::ios::in | std::ios::binary);
	fEntrada.read(reinterpret_cast<char *>(&len), sizeof(size_t));
	if (len > 0) {
		players.resize(len);
		PlayerData *tmp = new PlayerData[len];
		fEntrada.read(reinterpret_cast<char *>(tmp), sizeof(PlayerData) *len);
		for (int i = 0; i < len; i++)
		{
			std::cout << players[i].name << std::endl;
			players[i] = tmp[i];
		}

		//delete[]tmp;
		fEntrada.close();

	}

}

void RankingData::InitRects()
{
	rankingRect.Init(RANKING_EDGES, RANKING_EDGES, 300, 70);

	for (int i = 0; i < players.size(); i++) {
		numRects[i].Init(RANKING_EDGES, i * (50 + RANKING_EDGES) + RANKING_EDGES + 100, 50, 50);
		nameRects[i].Init(100 + RANKING_EDGES, i * (50 + RANKING_EDGES) + RANKING_EDGES + 100, players[i].name.length() * 50, 50);
		scoreRects[i].Init(SCREEN_WIDTH - 200, i * (50 + RANKING_EDGES) + RANKING_EDGES + 100, 150, 50);

	}

}
