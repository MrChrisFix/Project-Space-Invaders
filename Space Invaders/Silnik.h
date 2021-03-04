#pragma once

#include "Biblioteki.h"
#include "Gracz.h"
#include "Bullet.h"

#include <map>
#include <vector>

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
	std::vector<Bullet*> pociki;

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
	void updatePlayer();
	void updateBullets();
	void update();

	void render();

};

