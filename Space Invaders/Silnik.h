#pragma once

#include "MainMenu.h"
#include "PauseMenu.h"
#include "ZapisWyniku.h"
#include "InGame.h"

#include <iostream>
#include "MenuManager.h"

class Silnik
{
	//Zmienne
	const short int WindowHeight = 720, WindowLength = 1280;

	int punkty;


	//Obiekty
	sf::RenderWindow* window;
	sf::Event ev;

	InGame* Gra;
	MenuManager* Menus;

	//Zasoby
	sf::Font Czcionka;

	//Funckje prywatne
	void initVariables();
	void initWindow();
	void initMenu();

	void loadFont();


public:
	Silnik();
	~Silnik();

	bool isRunning();


	void pollEvent();
	void update();

	void render();

};