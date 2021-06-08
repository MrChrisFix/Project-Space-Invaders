#include "InGame.h"
#include <iostream>

void InGame::initGracz()
{
	this->gracz = new Gracz(textures["STATEK_GRACZA"], 640.f - this->textures["STATEK_GRACZA"]->getSize().x, 600.f);
}

void InGame::loadTextures()
{
	try
	{
		//Tekstury podstawowe

		this->textures["STATEK_GRACZA"] = new sf::Texture();
		if (!this->textures["STATEK_GRACZA"]->loadFromFile("Textures/Ship1.png"))
		{
			throw "STATEK_GRACZA";
		}

		this->textures["POCISK_GRACZA"] = new sf::Texture();
		if (!this->textures["POCISK_GRACZA"]->loadFromFile("Textures/Player_Bullet.png"))
		{
			throw "POCISK_GRACZA";
		}

		this->textures["SERCE"] = new sf::Texture();
		if (!this->textures["SERCE"]->loadFromFile("Textures/Heart.png"))
		{
			throw "HEART";
		}

		//Tekstury przeciwnikow

		this->textures["RED_ALIEN1"] = new sf::Texture();
		if (!this->textures["RED_ALIEN1"]->loadFromFile("Textures/Red_Alien1.png"))
		{
			throw "RED_ALIEN1";
		}

		this->textures["RED_ALIEN2"] = new sf::Texture();
		if (!this->textures["RED_ALIEN2"]->loadFromFile("Textures/Red_Alien2.png"))
		{
			throw "RED_ALIEN2";
		}

		this->textures["GREEN_ALIEN1"] = new sf::Texture();
		if (!this->textures["GREEN_ALIEN1"]->loadFromFile("Textures/Green_Alien1.png"))
		{
			throw "GREEN_ALIEN1";
		}

		this->textures["GREEN_ALIEN2"] = new sf::Texture();
		if (!this->textures["GREEN_ALIEN2"]->loadFromFile("Textures/Green_Alien2.png"))
		{
			throw "GREEN_ALIEN2";
		}

		this->textures["BLUE_ALIEN1"] = new sf::Texture();
		if (!this->textures["BLUE_ALIEN1"]->loadFromFile("Textures/Blue_Alien1.png"))
		{
			throw "BLUE_ALIEN1";
		}

		this->textures["BLUE_ALIEN2"] = new sf::Texture();
		if (!this->textures["BLUE_ALIEN2"]->loadFromFile("Textures/Blue_Alien2.png"))
		{
			throw "BLUE_ALIEN2";
		}
	}
	catch (const char* Error)
	{
		std::cout << "Blad przy ladowaniu tekstury " << Error << std::endl;
		this->error = true;
	}
}

void InGame::initOther()
{
	for (int i = 0; i < 3; i++)
	{
		this->Serce[i].setTexture(*this->textures["SERCE"]);
		this->Serce[i].setScale(4.f, 4.f);
		this->Serce[i].setPosition(1100.f + i * 60.f, 680.f);
	}

	this->PKT.setFont(*this->czcionka);
	this->PKT.setPosition(0.f, 640.f);
	this->PKT.setCharacterSize(24);

}

void InGame::updateText()
{
	this->PKT.setString( "Punkty: \n" + std::to_string(this->punkty));
}

void InGame::resetGame()
{
	this->przeciwnicy.restart(this->textures);

	this->pociski.clear();

	this->gracz->restartStats();

	this->punkty = 0;

	this->Koniec = false;
}

InGame::InGame(const short int* WinHeight, const short int* WinLength, sf::Font* font)
{
	this->WindowHeight = WinHeight;
	this->WindowLength = WinLength;
	this->error = false;
	this->Koniec = false;
	this->punkty = 0;
	this->czcionka = font;

	this->loadTextures();

	this->initGracz();
	this->initOther();

	this->przeciwnicy.restart(this->textures);
}

InGame::~InGame()
{
	delete this->gracz;

	//Usuwanie tekstur
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	this->WindowHeight = nullptr;
	this->WindowLength = nullptr;
	this->czcionka = nullptr;

	//oz usuwa MenuManager
	this->oz = nullptr;
}

void InGame::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->gracz->move(-1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->gracz->move(1.f);

	//Uderzenie przez pocisk
	auto licznik = this->pociski.begin();
	for (auto& i : this->pociski)
	{
		if (i->getGBounds().intersects(this->gracz->getGBounds()) && !i->isPlayerBullet())
		{
			this->gracz->stracZycie();
			this->pociski.erase(licznik);
			break;
		}
		licznik++;
	}

	//Przeciwnik wlecia³ w statek
	auto licznik2 = this->przeciwnicy.getEnemies()->begin();
	auto temp = this->przeciwnicy.getEnemies();
	for (auto& i : *temp)
	{
		if (i->getGBounds().intersects(this->gracz->getGBounds()))
		{
			this->gracz->stracZycie();
			temp->erase(licznik2);
			break;
		}
		licznik2++;
	}


	if (this->gracz->getZycia() < 1)
	{
		this->Koniec = true;
	}
}

void InGame::updateBullets()
{
	//Ruch pociskw
	for (auto& i : this->pociski)
		i->move();

	//Pojawianie sie pociskow po wcisniecieue spacji
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->gracz->canAttack())
		this->pociski.push_back(std::make_shared<Bullet>(
			this->textures["POCISK_GRACZA"],
			true,
			this->gracz->getGBounds().left + this->gracz->getGBounds().width / 2 - this->textures["POCISK_GRACZA"]->getSize().x,
			this->gracz->getGBounds().top - textures["POCISK_GRACZA"]->getSize().y * 2.f)
		);

	//Usuwanie pociskow, ktore sa poza ekranem
	unsigned short int licznik = 0;
	for (auto& i : this->pociski)
	{
		if (i != nullptr)
		{
			if (i->getGBounds().top + i->getGBounds().height < 0 || i->getGBounds().top > *this->WindowHeight)
			{
				this->pociski.erase(this->pociski.begin() + licznik);
				licznik--;
			}
		}
		licznik++;
	}

	//Usuwanie dwóch pociskow, ktore sie trafily
	unsigned short int licznik_i = 0;
	for (auto& i : this->pociski)
	{
		unsigned short int licznik_j = 0;
		for (auto& j : this->pociski)
		{
			if (i != nullptr && j != nullptr && i != j)
			{
				if (i->getGBounds().intersects(j->getGBounds()) && i->isPlayerBullet())
				{
					if (licznik_i > licznik_j)
					{
						pociski.erase(pociski.begin() + licznik_i);
						pociski.erase(pociski.begin() + licznik_j);
					}
					else
					{
						pociski.erase(pociski.begin() + licznik_j);
						pociski.erase(pociski.begin() + licznik_i);
					}
						if (licznik_i > 0)	licznik_i--;
						if (licznik_j > 0)  licznik_j--;
				}
			}
			licznik_j++;
		}
		licznik_i++;
	}
}

bool InGame::Error()
{
	return this->error;
}

bool InGame::GameOver()
{
	return this->Koniec;
}

int InGame::getWynik()
{
	return this->punkty;
}

void InGame::setOZ(Odczyt_Zapis* OZ)
{
	this->oz = OZ;
}

void InGame::wczytaj()
{
	this->przeciwnicy.getEnemies()->clear();
	this->pociski.clear();


	this->oz->odczytaj(this->textures, this->przeciwnicy.getEnemies(), this->pociski, this->gracz, *this->przeciwnicy.getLewo(), this->punkty);
}

void InGame::zapisz()
{
	this->oz->zapisz(*this->przeciwnicy.getEnemies(), this->pociski, this->gracz, this->przeciwnicy.getLewo(), this->punkty);
}

void InGame::update()
{
	this->updatePlayer();
	this->updateBullets();
	this->updateText();

	this->przeciwnicy.updateEnemies(this->pociski, this->textures["POCISK_GRACZA"], this->punkty);
	if (this->przeciwnicy.allDestroyed())	this->Koniec = true; //TODO: Nowa fala

	this->gracz->update();

}

void InGame::render(sf::RenderTarget& target)
{
	this->gracz->render(target);

	for (auto& i : this->pociski)
		i->render(target);
	this->przeciwnicy.render(target);

	for (int i = 0; i < gracz->getZycia(); i++)
		target.draw(Serce[i]);

	target.draw(this->PKT);
}
