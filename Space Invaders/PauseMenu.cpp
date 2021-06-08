#include "PauseMenu.h"

; void PauseMenu::initButtons()
{
	//Kontynuuj
	sf::Text* temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Kontynuuj gre");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 100 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);

	//Zapisz gre
	temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Zapisz gre");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 200 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);

	//Wczytaj gre
	temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Wczytaj gre");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 300 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);

	//Poddaj sie
	temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Poddaj sie");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 400 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);
}

int PauseMenu::detectButtonClick(bool& pressed)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Kontynuuj
			return 1;
		}
		if (this->buttons[1]->getGlobalBounds().contains(mysz2))
		{
			//Zapsiz gre
			return 2;
		}
		if (this->buttons[2]->getGlobalBounds().contains(mysz2))
		{
			//Wczytaj gre
			return 3;
		}
		if (this->buttons[3]->getGlobalBounds().contains(mysz2))
		{
			//Wyjdz
			return 4;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;

	return 0;
}

PauseMenu::PauseMenu(sf::Font* font_, sf::RenderWindow* target_) : MenuType(font_, target_)
{
	this->initButtons();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{

}

void PauseMenu::render()
{
	for (size_t i = 0; i < this->buttons.size(); i++)
		target->draw(*this->buttons[i]);
}
