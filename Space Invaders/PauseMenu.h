#pragma once
#include "MenuType.h"

class PauseMenu : public MenuType
{
protected:
	void initButtons() override;

public:
	PauseMenu(sf::Font* font_, sf::RenderWindow* target_);
	~PauseMenu();

	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;
};