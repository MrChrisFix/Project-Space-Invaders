#include "MainMenu.h"
#include <iostream>
#include <exception>

void MainMenu::initButtons()
{
	this->buttons.push_back(new sf::Text("Graj", *this->czcionka));
	this->buttons.push_back(new sf::Text("Ranking", *this->czcionka));
	//this->buttons.push_back(new sf::Text("Pomoc", *this->czcionka)); //TODO
	this->buttons.push_back(new sf::Text("Wyjdz z gry", *this->czcionka));
	this->buttons.push_back(new sf::Text("Cofnij", *this->czcionka));

	for (size_t i = 0; i < buttons.size(); i++)
	{
		this->buttons[i]->setPosition(640 - this->buttons[i]->getGlobalBounds().width / 2, 200 + this->buttons[i]->getGlobalBounds().height + 100 * i);
	}

	//Texts
	this->SpaceInvaders.setFont(*this->czcionka);
	this->SpaceInvaders.setString("SPACE INVADERS");
	this->SpaceInvaders.setCharacterSize(40);
	this->SpaceInvaders.setPosition(640.f - this->SpaceInvaders.getGlobalBounds().width / 2, 80.f);
}

MainMenu::MainMenu(sf::Font* font_, sf::RenderWindow* target_) : MenuType(font_, target_)
{
	this->initButtons();
}

MainMenu::~MainMenu()
{
}

int MainMenu::detectButtonClick(bool& pressed)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Graj
			return 1;
		}
		if (this->buttons[1]->getGlobalBounds().contains(mysz2))
		{
			//Ranking
			return 2;
		}
		if (this->buttons[2]->getGlobalBounds().contains(mysz2))
		{
			//Wyjdz z gry
			return 3;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;

	return 0;
}

void MainMenu::update()
{
}

void MainMenu::render()
{
	for (int i = 0; i < 3; i++)
	{
		this->target->draw(*this->buttons[i]);
	}
	this->target->draw(this->SpaceInvaders);
}