#pragma once
#include "Gracz.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Timer.h"

#include "EnemyManager.h"
#include "Odczyt_Zapis.h"

class InGame
{
	const short int *WindowHeight, *WindowLength;

	bool error;
	bool Koniec;

	int punkty;

	sf::Text PKT; ///< Napis z liczba punktow

	sf::Sprite Serce[3];

	//Obiekty
	Gracz* gracz;
	EnemyManager przeciwnicy;

	Odczyt_Zapis* oz;

	std::vector<std::shared_ptr<Bullet>> pociski;


	//Zasoby
	std::map<std::string, sf::Texture*> textures;
	sf::Font* czcionka;


	//Funckje prywatne
	void initGracz();

	void loadTextures();

	void initOther();

	void updateText();


public:
	InGame(const short int *WinHeight, const short int *WinLength, sf::Font * font);
	~InGame();

	void resetGame();


	void updatePlayer();
	void updateBullets();

	bool Error();
	bool GameOver();
	int getWynik();

	//Odczyt i zapis
	void setOZ(Odczyt_Zapis* OZ);
	void wczytaj();
	void zapisz();

	void update();

	void render(sf::RenderTarget& target);

};

