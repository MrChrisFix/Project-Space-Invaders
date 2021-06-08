#include "PlayMenu.h"

void PlayMenu::initButtons()
{
	//Nowa gra
	sf::Text* temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Nowa gra");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 100 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);

	//Wczytaj gre
	temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Wczytaj gre");
	temp->setPosition(640 - temp->getGlobalBounds().width / 2, 200 + temp->getGlobalBounds().height);
	this->buttons.push_back(temp);

	temp = new sf::Text();
	temp->setFont(*czcionka);
	temp->setString("Cofnij");
	temp->setPosition(0, 720 - temp->getGlobalBounds().height);
	temp->setCharacterSize(20);
	this->buttons.push_back(temp);

	temp = nullptr;
}

PlayMenu::PlayMenu(sf::Font* font_, sf::RenderWindow* target_) : MenuType(font_, target_)
{
	this->initButtons();
}

PlayMenu::~PlayMenu()
{
}

int PlayMenu::detectButtonClick(bool& pressed)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Nowa gra
			return 1;
		}
		if (this->buttons[1]->getGlobalBounds().contains(mysz2))
		{
			//Wczytaj gre
			return 2;
		}
		if (this->buttons[2]->getGlobalBounds().contains(mysz2))
		{
			//Cofnij
			return 3;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;

	return 0;
}

void PlayMenu::update()
{

}

void PlayMenu::render()
{
	for (size_t i = 0; i < this->buttons.size(); i++)
		target->draw(*this->buttons[i]);
}
