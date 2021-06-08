#pragma once
#include "MenuType.h"
class ZapisWyniku : public MenuType
{
	
	void initButtons() override;
	int punkty;
	std::string wpisany_nick;

	char zatwierdzone;


public:
	ZapisWyniku(sf::Font* font, sf::RenderWindow* target, int pkt);
	~ZapisWyniku();

	void giveCharacter(sf::Event evnt);

	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;

	std::string getNick();

	int getWynik();

};

