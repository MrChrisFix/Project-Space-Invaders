#include "Silnik.h"


void Silnik::initVariables()
{
    this->window = nullptr;
}

void Silnik::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(this->WindowLength, this->WindowHeight), "Space Invaders - by Christian Fikus", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

Silnik::Silnik()
{

    this->initVariables();
    this->initWindow();

}

Silnik::~Silnik()
{
    delete this->window;

}

bool Silnik::isRunning()
{
    return this->window->isOpen();
}

void Silnik::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			//zamykanie okna
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		default:
			break;
		}
	}
    
}

void Silnik::update()
{
	this->pollEvent();

}

void Silnik::render()
{
	//Czyszczenie
	this->window->clear();

	//Rysowanie



	//Wyswietlanie
	this->window->display();
	
}
