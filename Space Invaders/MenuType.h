#pragma once
#include "Biblioteki.h"

class MenuType
{
protected:
	sf::Font* czcionka;

	std::vector<sf::Text*> buttons;

	sf::RenderWindow* target;


	virtual void initButtons() = 0;
	virtual int detectButtonClick(bool& pressed) = 0;

public:
	MenuType(sf::Font* font, sf::RenderWindow* target);
	virtual ~MenuType();

	virtual void update() = 0;

	virtual void render() = 0;
};
