#include "Silnik.h"

void Silnik::initVariables()
{
    this->window = nullptr;

	this->punkty = 0;
}

void Silnik::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(this->WindowLength, this->WindowHeight), "Space Invaders - by Christian Fikus", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Silnik::initMenu()
{
	this->Menus = new MenuManager(&this->Czcionka, this->window);

	this->Gra = new InGame(&this->WindowHeight, &this->WindowLength, &this->Czcionka);


	Odczyt_Zapis* temp = new Odczyt_Zapis(&this->Czcionka, this->window);
	this->Menus->setOZ(temp);
	this->Gra->setOZ(temp);
	temp = nullptr;
}

void Silnik::loadFont()
{
	if (!this->Czcionka.loadFromFile("Font/PressStart2P-Regular.ttf"))
	{
		std::cout << "Nie zaladowano czcionki!\n";
		this->window->close();
	}
}

Silnik::Silnik()
{

	this->loadFont();
    this->initVariables();
    this->initWindow();

	this->initMenu();
}

Silnik::~Silnik()
{
    delete this->window;

	delete this->Menus;

	delete this->Gra;
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
			//Zamykanie okna
		case sf::Event::Closed:
		{
			this->window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->Menus->Escape();
			}
			break;
		}
		case sf::Event::TextEntered:
		{
			this->Menus->Text(this->ev);
			break;
		}

		default:
			break;
		}
	}
    
}

void Silnik::update()
{
	this->pollEvent();

	switch (Menus->update())

	{
	case 0: //Gra
	{
		this->Gra->update();

		if (this->Gra->GameOver())
		{
			this->Menus->koniecGry(this->Gra->getWynik());
		}
		break;
	}
	case 1: // Zamknij okno
	{
		this->window->close();
		break;
	}
	case 2: //reset game
	{
		this->Gra->resetGame();
		break;
	}
	case 3: //Zapis gry
	{
		this->Gra->zapisz();
		break;
	}
	case 4: //Odczyt gry
	{
		this->Gra->wczytaj();
		break;
	}
	default:
		break;
	}

}

void Silnik::render()
{
	//Czyszczenie
	this->window->clear();

	//Rysowanie
	if (this->Menus->render())
	{
		this->Gra->render(*this->window);
	}

	//Wyswietlanie
	this->window->display();
}
