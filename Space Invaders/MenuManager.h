#pragma once
#include "Biblioteki.h"
#include "PauseMenu.h"
#include "MainMenu.h"
#include "PlayMenu.h"
#include "ZapisWyniku.h"
#include "Odczyt_Zapis.h"
#include "Ranking.h"

class MenuManager
{
private:
	enum class MENU{Main = 0, Pause, Play, Ranking, ZapisWyniku, Odczyt, Zapis, Other} menu;

	bool pressed_button;

	MENU lastMenu = MENU::Main;

	sf::RenderWindow* target;
	sf::Font* czcionka;

	//Menus
	MainMenu* Main;
	PauseMenu* Pause;
	PlayMenu* Play;
	Ranking* ranking;
	ZapisWyniku* Wyniki;

	Odczyt_Zapis* oz;


	//Prywatne funkcje
	void initMenus();

public:
	MenuManager(sf::Font* font_, sf::RenderWindow* target_);
	~MenuManager();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="n">0->Menu;
	///	1->Pause;
	///	2->Play;
	///	3->ZapisWyniku; ...</param>
	void setState(int n);

	void Escape();

	void koniecGry(int punkty);

	void Text(sf::Event ev);

	void setOZ(Odczyt_Zapis* OZ);

	int update();

	bool render();

};