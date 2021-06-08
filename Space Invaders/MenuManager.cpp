#include "MenuManager.h"

void MenuManager::initMenus()
{
	this->Main = new MainMenu(this->czcionka, this->target);
	this->Pause = new PauseMenu(this->czcionka, this->target);
	this->Play = new PlayMenu(this->czcionka, this->target);
	this->ranking = new Ranking(this->czcionka, this->target);

	this->menu = MENU::Main;

	this->Wyniki = nullptr;
}

MenuManager::MenuManager(sf::Font* font_, sf::RenderWindow* target_)
{
	this->czcionka = font_;
	this->target = target_;

	this->initMenus();
}

MenuManager::~MenuManager()
{
	delete this->Main;
	delete this->Pause;
	delete this->Play;
	delete this->ranking;
	czcionka = nullptr;
	target = nullptr;
	if(Wyniki != nullptr) delete this->Wyniki;

	delete this->oz;
}

void MenuManager::setState(int n)
{
	this->menu = static_cast<MENU>(n);
}

void MenuManager::Escape()
{
	if (this->menu == MENU::Other)
		this->menu = MENU::Pause;
	else if (this->menu == MENU::Pause)
		this->menu = MENU::Other;
}

void MenuManager::koniecGry(int punkty)
{
	this->Wyniki = new ZapisWyniku(this->czcionka, this->target, punkty);
	this->menu = MENU::ZapisWyniku;
}

void MenuManager::Text(sf::Event ev)
{
	if (this->menu == MENU::ZapisWyniku && this->Wyniki != nullptr)
	{
		this->Wyniki->giveCharacter(ev);
	}
}

void MenuManager::setOZ(Odczyt_Zapis* OZ)
{
	this->oz = OZ;
}

/// <summary>
/// 
/// </summary>
/// <returns>0 -> Gra; 1 -> </returns>
int MenuManager::update()
{
	switch (this->menu)
	{
	case MENU::Main:
	{
		int klik = 0;
		klik = this->Main->detectButtonClick(this->pressed_button);
		if (klik == 1) this->menu = MENU::Play;
		if (klik == 2) this->menu = MENU::Ranking;
		if (klik == 3) return 1;
		break;
	}
	case MENU::Pause:
	{
		int klik = 0;
		klik = this->Pause->detectButtonClick(this->pressed_button);
		if (klik == 1)
		{	//Powrot do gry
			this->menu = MENU::Other;
		}
		if (klik == 2)
		{	//Zapisz gre
			this->menu = MENU::Zapis;
			this->lastMenu = MENU::Pause;
		}
		if (klik == 3)
		{	//Wczytaj gre
			this->menu = MENU::Odczyt;
			this->lastMenu = MENU::Pause;
		}
		if (klik == 4)
		{	//Poddaj sie
			this->menu = MENU::Main; //TODO wypisawanie nicku i zapis punktow
			return 2;
		}
		break;
	}
	case MENU::Play:
	{
		int klik = 0;
		klik = this->Play->detectButtonClick(this->pressed_button);
		if (klik == 1) this->menu = MENU::Other; //rozpoczyna gre
		if (klik == 2)
		{
			this->menu = MENU::Odczyt;
			this->lastMenu = MENU::Play;
		}
		if (klik == 3) this->menu = MENU::Main;
		break;
	}
	case MENU::Ranking:
	{
		int klik = 0;
		klik = this->ranking->detectButtonClick(this->pressed_button);
		if (klik == 1) this->menu = MENU::Main; 
		break;
	}
	case MENU::ZapisWyniku:
	{
		if (this->Wyniki != nullptr)
		{
			this->Wyniki->update();
		}
		else this->menu = MENU::Main; //Gdyby cos poszlo nie tak

		int klik = 0;
		klik = this->Wyniki->detectButtonClick(this->pressed_button);
		if (klik == 1)
		{	//Zatwierdz
			this->menu = MENU::Main;
			this->ranking->dodajDoRankingu(this->Wyniki->getNick(), this->Wyniki->getWynik());
			delete this->Wyniki;
			this->Wyniki = nullptr;
			return 2;
		}
		if (klik == 2)
		{	//Nie zatwierdzac
			this->menu = MENU::Main;
			delete this->Wyniki;
			this->Wyniki = nullptr;
			return 2;
		}
		break;
	}
	case MENU::Odczyt:
	{
		int klik = 0;
		klik = this->oz->detectButtonClick(this->pressed_button, false);
		if (klik == 2)
		{
			this->menu = MENU::Other;
			return 4;
		}
		if (klik == 1) //cofnij
		{
			this->menu = this->lastMenu;
		}
		break;
	}
	case MENU::Zapis:
	{
		int klik = 0;
		klik = this->oz->detectButtonClick(this->pressed_button, true);
		if (klik == 2)
		{
			return 3;
		}
		if (klik == 1) //cofnij
		{
			this->menu = this->lastMenu;
		}
		break;
	}
	default:
		return 0;
		break;
	}

	return -1;
}

bool MenuManager::render()
{
	switch (this->menu)
	{
	case MENU::Main:
	{
		this->Main->render();
		break;
	}
	case MENU::Pause:
	{
		this->Pause->render();
		break;
	}
	case MENU::Play:
	{
		this->Play->render();
		break;
	}
	case MENU::Ranking:
	{
		this->ranking->render();
		break;
	}
	case MENU::ZapisWyniku:
	{
		if (this->Wyniki != nullptr)
		{
			this->Wyniki->render();
		}
		else this->menu = MENU::Main; //Gdyby cos poszlo nie tak
		break;
	}
	case MENU::Zapis:
	{
		this->oz->render();
		break;
	}
	case MENU::Odczyt:
	{
		this->oz->render();
		break;
	}
	default:
	{
		return true;
		break; 
	}
	}

	return false;
}
