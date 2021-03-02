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

void Silnik::initGracz()
{
	gracz = new Gracz(textures["STATEK_GRACZA"]);
}

void Silnik::loadTextures()
{
	this->textures["STATEK_GRACZA"] = new sf::Texture();
	this->textures["STATEK_GRACZA"]->loadFromFile("Textures/ship.png");
}

Silnik::Silnik()
{

    this->initVariables();
    this->initWindow();
	this->loadTextures();
	this->initGracz();

}

Silnik::~Silnik()
{
    delete this->window;

	//Usuwanie tekstur
	for (auto &i : textures)
	{
		delete i.second;
	}
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

	this->gracz->render(*this->window);

	//Wyswietlanie
	this->window->display();
	
}
