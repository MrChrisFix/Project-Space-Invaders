#pragma once
#include "MenuType.h"
#include "Para.h"

class Ranking : public MenuType
{
	sf::Text Ranking_text;

	Para<std::string, unsigned int>* wyniki;

	void initButtons() override;
	void loadRanking();
	void restartRanking();
	void saveRanking();

public:
	Ranking(sf::Font* font, sf::RenderWindow* target);
	~Ranking();


	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;

	void dodajDoRankingu(std::string nick, unsigned int wynik);
};

