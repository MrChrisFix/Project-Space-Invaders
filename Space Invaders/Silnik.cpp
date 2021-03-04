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
	//TODO: sprawdzenie czy tekstury siê za³adowa³y

	this->textures["STATEK_GRACZA"] = new sf::Texture();
	this->textures["STATEK_GRACZA"]->loadFromFile("Textures/Ship1.png"); /////

	this->textures["RED_ALIEN"] = new sf::Texture();
	this->textures["RED_ALIEN"]->loadFromFile("Textures/Red_Alien1.png");

	this->textures["POCISK_GRACZA"] = new sf::Texture();
	this->textures["POCISK_GRACZA"]->loadFromFile("Textures/Player_Bullet.png");
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

	delete this->gracz;

	//Usuwanie tekstur
	for (auto &i : this-> textures)
	{
		delete i.second;
	}
	//Usuwanie pociskow
	for (auto &i : this->pociki)
	{
		delete i;
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

void Silnik::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->gracz->move(-1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->gracz->move(1.f);


}

void Silnik::updateBullets()
{
   	for (auto& i : this->pociki)
		i->move();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->gracz->canAttack())
		this->pociki.push_back(new Bullet(this->textures["POCISK_GRACZA"], true, this->gracz->getGBounds().left+this->gracz->getGBounds().width/2, this->gracz->getGBounds().top));

	unsigned short int licznik = 0;
	for (auto& i : this->pociki)
	{
		if (i->getGBounds().top + i->getGBounds().height < 0 || i->getGBounds().top > this->WindowHeight)
		{
			delete i;
			this->pociki.erase(this->pociki.begin() + licznik);
			licznik--;

		}
		licznik++;
	}

}


void Silnik::update()
{
	this->pollEvent();
	this->updatePlayer();
	this->updateBullets();

	this->gracz->update();

}

void Silnik::render()
{
	//Czyszczenie
	this->window->clear();

	//Rysowanie

	this->gracz->render(*this->window);

	for (auto &i : this->pociki)
		i->render(*this->window);

	//Wyswietlanie
	this->window->display();
	
}
