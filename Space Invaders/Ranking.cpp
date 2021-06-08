#include "Ranking.h"
#include <fstream>

void Ranking::initButtons()
{
	this->buttons.push_back(new sf::Text("Cofnij", *this->czcionka));
	this->buttons[0]->setFont(*this->czcionka);
	this->buttons[0]->setPosition(0, 720 - this->buttons[0]->getGlobalBounds().height);
	this->buttons[0]->setCharacterSize(20);
}

void Ranking::loadRanking()
{
	std::ifstream plik;
	plik.open("Ranking.txt");
	if (plik.is_open() && !plik.eof())
	{
		auto p = wyniki;
		while (!plik.eof())
		{
			if (plik.peek() == -1) break;
			auto temp = new Para<std::string, unsigned int>;

			std::string nick;
			unsigned int wynik;
			plik >> nick;
			plik >> wynik;
			temp->add(nick, wynik);
			if (p)
			{
				p->setNext(temp);
				p = p->getNext();
			}
			else
			{
				wyniki = temp;
				p = temp;
			}
		}

		plik.close();
		this->restartRanking();
	}
}

void Ranking::restartRanking()
{
	Ranking_text.setString("");
	auto p = this->wyniki;
	for (int i = 0; i < 10; i++)
	{
		if (p)
		{
			std::string odstep = "    ";
			for (size_t i = 0; i < 10 - p->getFirst().size(); i++)	odstep += " ";
			Ranking_text.setString(Ranking_text.getString() + p->getFirst() + odstep + std::to_string(p->getSecond()) + "\n");
			p = p->getNext();
		}

		else break;
	}


	this->Ranking_text.setFont(*this->czcionka);
	this->Ranking_text.setPosition(640 - this->Ranking_text.getGlobalBounds().width / 2, 100.f);
}

void Ranking::saveRanking()
{
	std::ofstream plik;
	plik.open("Ranking.txt");
	if (plik.is_open())
	{
		auto p = wyniki;
		while (p)
		{
			plik << p->getFirst() << " " << p->getSecond();
			if (p->getNext() != nullptr) plik << std::endl;

			p = p->getNext();
		}

		plik.close();
	}
}

Ranking::Ranking(sf::Font* font, sf::RenderWindow* target) : MenuType(font, target)
{
	this->initButtons();

	this->loadRanking();
}

Ranking::~Ranking()
{
	this->saveRanking();

	while (wyniki)
	{
		auto p = wyniki->getNext();
		delete wyniki;
		wyniki = p;
	}
}

int Ranking::detectButtonClick(bool& pressed)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
	{
		pressed = true;
		sf::Vector2i mysz1 = sf::Mouse::getPosition(*this->target);
		sf::Vector2f mysz2 = this->target->mapPixelToCoords(mysz1);
		if (this->buttons[0]->getGlobalBounds().contains(mysz2))
		{
			//Cofnij
			return 1;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed)
		pressed = false;
	return 0;
}

void Ranking::update()
{
}

void Ranking::render()
{
	target->draw(this->Ranking_text);

	for (int i = 0; i < this->buttons.size(); i++)
		this->target->draw(*buttons[i]);
}

void Ranking::dodajDoRankingu(std::string nick, unsigned int wynik)
{
	auto nowy = new Para<std::string, unsigned int>;
	nowy->add(nick, wynik);

	//Pusty ranking
	if (this->wyniki == nullptr)
	{
		this->wyniki = nowy;
		restartRanking();
		return;
	}
	//Nowy jest wiekszy niz pierwszy w rankingu
	if (this->wyniki->getSecond() < nowy->getSecond())
	{
		nowy->setNext(this->wyniki);
		this->wyniki = nowy;
		restartRanking();
		return;
	}

	auto p = this->wyniki;
	while (p)
	{
		if (p->getNext() == nullptr)
		{
			p->setNext(nowy);
			restartRanking();
			return;
		}
		else
		{
			if (p->getNext()->getSecond() > nowy->getSecond())
			{
				p = p->getNext();
			}
			else
			{
				nowy->setNext(p->getNext());
				p->setNext(nowy);
				restartRanking();
				return;
			}
		}
	}

}
