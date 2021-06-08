#pragma once
#include "Biblioteki.h"
#include "MenuType.h"
#include <fstream>

class MainMenu : public MenuType
{
	sf::Text SpaceInvaders;

	void initButtons() override;

public:
	MainMenu(sf::Font* font, sf::RenderWindow* target);
	~MainMenu();

	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;

};

