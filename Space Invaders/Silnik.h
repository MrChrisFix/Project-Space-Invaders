#pragma once

#include "Biblioteki.h"
#include "Gracz.h"

#include <map>

class Silnik
{
	//Zmienne
	const short int WindowHeight = 720, WindowLength = 1280;



	//Obiekty
	sf::RenderWindow* window;
	sf::Event ev;

	Gracz* gracz;

	//Zasoby
	std::map<std::string, sf::Texture*> textures;

	//Funckje prywatne
	void initVariables();
	void initWindow();
	void initGracz();
	void loadTextures();


public:
	Silnik();
	~Silnik();

	bool isRunning();


	void pollEvent();
	void update();

	void render();

};

