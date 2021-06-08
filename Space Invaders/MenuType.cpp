#include "MenuType.h"

MenuType::MenuType(sf::Font* font, sf::RenderWindow* target_)
{
	this->czcionka = font;

	this->target = target_;
}

MenuType::~MenuType()
{
	for (auto& i : this->buttons)
	{
		delete i;
	}
	buttons.clear();

	this->target = nullptr;
}
