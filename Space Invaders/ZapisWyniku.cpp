#include "ZapisWyniku.h"
#include <iostream>

void ZapisWyniku::initButtons()
{
	this->buttons.push_back(new sf::Text("Zatwierdz", *this->czcionka));
	this->buttons.push_back(new sf::Text("Nie dodawaj wyniku", *this->czcionka));

	this->buttons[1]->setCharacterSize(25);

	for (int i = 0; i < buttons.size(); i++)
	{
		this->buttons[i]->setPosition(640 - this->buttons[i]->getGlobalBounds().width / 2, 400 + this->buttons[i]->getGlobalBounds().height + 100 * i);
	}

	//Napis wynik
	this->buttons.push_back(new sf::Text("Wynik: " + std::to_string(punkty), *this->czcionka));
	this->buttons[2]->setPosition(640 - this->buttons[2]->getGlobalBounds().width / 2, 100 + this->buttons[2]->getGlobalBounds().height + 100);


}

ZapisWyniku::ZapisWyniku(sf::Font* font, sf::RenderWindow* target, int pkt) : MenuType(font, target)
{
	punkty = pkt;
	this->initButtons();
	this->zatwierdzone = 'n';
}

ZapisWyniku::~ZapisWyniku()
{
}

void ZapisWyniku::giveCharacter(sf::Event evnt)
{
	auto kod = evnt.text.unicode;

	if (kod == '\b' && this->wpisany_nick.size() > 0)
	{
		this->wpisany_nick.erase(this->wpisany_nick.size() - 1, 1);
	}
	else if (this->wpisany_nick.size() < 10 && kod > 47 && kod < 123)
	{
		this->wpisany_nick += static_cast<char>(evnt.text.unicode);
	}
	else if (kod == '\n' && this->wpisany_nick.size() > 0)
	{
		//TODO: dodaj Enter jako zapis
		zatwierdzone = 't';
	}

}

int ZapisWyniku::detectButtonClick(bool& pressed)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Zapisz
			if(this->wpisany_nick.size() > 0)	return 1;
			
		}
		if (this->buttons[1]->getGlobalBounds().contains(mysz2))
		{
			//Nie zapisuj
			return 2;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;
	return 0;
}

void ZapisWyniku::update()
{

}

void ZapisWyniku::render()
{
	for (int i = 0; i < 2; i++)
	{
		this->target->draw(*this->buttons[i]);
	}

	sf::Text Nick = sf::Text(this->wpisany_nick, *this->czcionka);
	Nick.setPosition(640 - Nick.getGlobalBounds().width / 2, 100 + Nick.getGlobalBounds().height);

	this->target->draw(Nick);

}

std::string ZapisWyniku::getNick()
{
	return this->wpisany_nick;
}

int ZapisWyniku::getWynik()
{
	return this->punkty;
}
