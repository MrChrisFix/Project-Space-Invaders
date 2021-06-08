#pragma once
#include "MenuType.h"
class PlayMenu : public MenuType
{
protected:
	void initButtons() override;

public:
	PlayMenu(sf::Font* font_, sf::RenderWindow* target_);
	~PlayMenu();

	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;
};

