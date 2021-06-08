#include "Odczyt_Zapis.h"

#include <fstream>

void Odczyt_Zapis::initButtons()
{
	for (int i = 1; i < 6; i++)
	{
		this->buttons.push_back(new sf::Text("Zapis" + std::to_string(i), *this->czcionka));

		this->buttons[i-1]->setPosition(640 - this->buttons[i-1]->getGlobalBounds().width / 2, 100 + this->buttons[i-1]->getGlobalBounds().height + 100 * (i-1));
	}

	this->buttons.push_back(new sf::Text("Cofnij", *this->czcionka, 20));
	this->buttons[5]->setPosition(0, 720 - this->buttons[3]->getGlobalBounds().height);
}

bool Odczyt_Zapis::czyIstnieje(int numer)
{
	std::ifstream plik;
	plik.open("Saves\\Zapis" + std::to_string(numer));
	if (plik.is_open())
	{
		plik.close();
		return true;
	}

	return false;
}

Odczyt_Zapis::Odczyt_Zapis(sf::Font* font, sf::RenderWindow* target) : MenuType(font, target)
{
	this->wybranyNumer = 0;

	this->initButtons();
}

Odczyt_Zapis::~Odczyt_Zapis()
{

}

void Odczyt_Zapis::zapisz(std::vector<std::shared_ptr<Enemy>> przeciwnicy, std::vector<std::shared_ptr<Bullet>> pociski, Gracz* player, bool lewo, int punkty)
{
	if (this->wybranyNumer == 0) return;

	std::ofstream plik;
	plik.open("Saves\\Zapis" + std::to_string(this->wybranyNumer), std::fstream::binary);
	if (plik.is_open())
	{
		plik << punkty << std::endl;
		plik << player->getGBounds().left << ' ' << player->getGBounds().top << ' ' << player->getZycia() << std::endl;

		//Przeciwnicy
		//W lewo?
		plik << lewo << std::endl;

		//Oddalenie
		plik << przeciwnicy[0]->getOddalenie() << std::endl;


		plik << przeciwnicy.size() << std::endl;

		for (size_t i = 0; i < przeciwnicy.size(); i++)
		{
			auto temp = przeciwnicy[i];
			plik << temp->Position().x << ' ' << temp->Position().y << ' ' << temp->ilePunktow() << std::endl;
		}

		//Pociski
		plik << pociski.size() << std::endl;
		for (size_t i = 0; i < pociski.size(); i++)
		{
			auto temp = pociski[i];
			plik << temp->getGBounds().left << ' ' << temp->getGBounds().top << ' ' << temp->isPlayerBullet() << std::endl;
		}

		plik.close();
	}
}


void Odczyt_Zapis::odczytaj(std::map<std::string, sf::Texture*> tekstury,
	std::vector<std::shared_ptr<Enemy>>* przeciwnicy, std::vector<std::shared_ptr<Bullet>>& pociski, Gracz* player, bool& lewo, int& punkty)
{
	if (this->wybranyNumer == 0) return;

	std::ifstream plik;
	plik.open("Saves\\Zapis" + std::to_string(this->wybranyNumer), std::fstream::binary);

	if (plik.is_open())
	{
		float x, y;
		int zycia;
		float oddalenie;

		plik >> punkty;
		plik >> x >> y >> zycia;

		player->setNew(x, y, zycia);

		plik >> lewo;
		plik >> oddalenie;

		//przeciwnicy
		int przec, pkt;
		plik >> przec; //liczba przeciwnikow
		for (int i = 0; i < przec; i++)
		{
			plik >> x >> y >> pkt;
			if (pkt == 1 || pkt == 2)
			{
				przeciwnicy->push_back(std::make_shared<Enemy>(
					tekstury["RED_ALIEN1"], tekstury["RED_ALIEN2"], x, y, pkt, oddalenie));
			}
			else if (pkt == 3 || pkt == 4)
			{
				przeciwnicy->push_back(std::make_shared<Enemy>(
					tekstury["BLUE_ALIEN1"], tekstury["BLUE_ALIEN2"], x, y, pkt, oddalenie));
			}
			else
			{
				przeciwnicy->push_back(std::make_shared<Enemy>(
					tekstury["GREEN_ALIEN1"], tekstury["GREEN_ALIEN2"], x, y, pkt, oddalenie));
			}
		}

		//Pociski
		int poc;
		bool playerBullet;
		plik >> poc; //liczba pociskow
		for (int i = 0; i < poc; i++)
		{
			plik >> x >> y >> playerBullet;
			pociski.push_back(std::make_shared<Bullet>(tekstury["POCISK_GRACZA"], playerBullet, x, y));
		}


		plik.close();
	}
}

//WIZUALNA

int Odczyt_Zapis::detectButtonClick(bool& pressed, bool czyZapis)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Zapis 1
			if (this->czyIstnieje(1) || czyZapis)
			{
				this->wybranyNumer = 1;
				return 2;
			}
		}
		if (this->buttons[1]->getGlobalBounds().contains(mysz2))
		{
			//Zapis 2
			if (this->czyIstnieje(2) || czyZapis)
			{
				this->wybranyNumer = 2;
				return 2;
			}
		}
		else if (this->buttons[2]->getGlobalBounds().contains(mysz2))
		{
			//Zapis 3
			if (this->czyIstnieje(3) || czyZapis)
			{
				this->wybranyNumer = 3;
				return 2;
			}
		}
		else if (this->buttons[3]->getGlobalBounds().contains(mysz2))
		{
			//Zapis 4
			if (this->czyIstnieje(4) || czyZapis)
			{
				this->wybranyNumer = 4;
				return 2;
			}
		}
		else if (this->buttons[4]->getGlobalBounds().contains(mysz2))
		{
			//Zapis 5
			if (this->czyIstnieje(5) || czyZapis)
			{
				this->wybranyNumer = 5;
				return 2;
			}
		}
		else if (this->buttons[5]->getGlobalBounds().contains(mysz2))
		{
			//Cofnij
			return 1;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;

	return 0;
}

int Odczyt_Zapis::detectButtonClick(bool& pressed)
{
	return 0;
}

void Odczyt_Zapis::update()
{
}

void Odczyt_Zapis::render()
{
	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->target->draw(*this->buttons[i]);
	}
}
